// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2014 Broadcom Corporation.
 * Copyright 2015 Free Electrons.
 */

#include <config.h>
#include <common.h>

#include <fastboot.h>
#include <image-sparse.h>

#include <linux/mtd/mtd.h>
#include <jffs2/jffs2.h>
#include <spi_flash.h>



struct fb_spi_sparse {
	struct mtd_info		*mtd;
	struct part_info	*part;
};


struct spi_flash *spiflash = NULL;

__weak int board_fastboot_erase_partition_setup(char *name)
{
	return 0;
}

__weak int board_fastboot_write_partition_setup(char *name)
{
	return 0;
}

static int fb_spi_lookup(const char *partname,
			  struct mtd_info **mtd,
			  struct part_info **part,
			  char *response)
{
	struct mtd_device *dev;
	int ret;
	u8 pnum;

	//if (spiflash == NULL) {
#ifdef CONFIG_DM_SPI_FLASH
		struct udevice *new;
		char *spidev;

		spidev = env_get("fastboot_spidev");
		/* speed and mode will be read from DT */
		if (spidev == NULL) {
			ret = spi_flash_probe_bus_cs(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
							 CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE,
							 &new);
		} else {
			int bus = 0, cs = 0;

			if (strlen(spidev) > 5 && spidev[4] == '.') {
				bus = spidev[3] - '0';
				cs  = spidev[5] - '0';
				if (bus >= 0 && bus <= 9 && cs >= 0 && cs <= 9) {
				} else {
					bus = 0;
					cs  = 0;
				}
			}
            printf("linsenhui:bus:%d,cs:%d\n",bus,cs);
			ret = spi_flash_probe_bus_cs(bus, cs,
							 CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE,
							 &new);
		}

		if (ret) {
			env_set_default("spi_flash_probe_bus_cs() failed", 0);
			return ret;
		}

		spiflash = dev_get_uclass_priv(new);
#else
		

		spiflash = spi_flash_probe(
		                 #ifdef CONFIG_WOKOO_SSI
		                          CONFIG_SF_DEFAULT_BUS+1,
		                 #else
						   CONFIG_SF_DEFAULT_BUS,
			             #endif
								   CONFIG_SF_DEFAULT_CS,
								   CONFIG_SF_DEFAULT_SPEED,
								   CONFIG_SF_DEFAULT_MODE);
#endif
	//}

	ret = mtdparts_init();
	if (ret) {
		pr_err("Cannot initialize MTD partitions\n");
		fastboot_fail("cannot init mtdparts", response);
		return ret;
	}

	printf("find partition: '%s'", partname);

	ret = find_dev_and_part(partname, &dev, &pnum, part);
	if (ret) {
		pr_err("cannot find partition: '%s'", partname);
		fastboot_fail("cannot find partition", response);
		return ret;
	}

	if (dev->id->type != MTD_DEV_TYPE_NOR) {
		pr_err("partition '%s' is not stored on a SPI device",
				partname);
		fastboot_fail("not a SPI device", response);
		return -EINVAL;
	}

	*mtd = get_mtd_device_nm(partname);
	return 0;
}

static int _fb_spi_erase(struct mtd_info *mtd, struct part_info *part)
{
	int ret;

	if (spiflash == NULL) {
		return -1;
	}

	printf("Erasing blocks 0x%llx to 0x%llx\n",
			part->offset, part->offset + part->size);

	ret = spi_flash_erase(spiflash, part->offset, part->size);
	if (ret)
		return ret;

	printf("........ erased 0x%llx bytes from '%s'\n",
			part->size, part->name);

	return 0;
}

static int _fb_spi_write(struct mtd_info *mtd, struct part_info *part,
			  void *buffer, u32 offset,
			  size_t length, size_t *written)
{
	if (spiflash == NULL) {
		return -1;
	}

	return spi_flash_write(spiflash, offset, length, buffer);
}

static lbaint_t fb_spi_sparse_write(struct sparse_storage *info,
		lbaint_t blk, lbaint_t blkcnt, const void *buffer)
{
	struct fb_spi_sparse *sparse = info->priv;
	size_t written = 0;
	int ret;

	ret = _fb_spi_write(sparse->mtd, sparse->part, (void *)buffer,
					blk * info->blksz,
					blkcnt * info->blksz, &written);
	if (ret < 0) {
		printf("Failed to write sparse chunk\n");
		return ret;
	}

	/*
	 * the return value must be 'blkcnt' ("good-blocks") plus the
	 * number of "bad-blocks" encountered within this space...
	 */
	return written / info->blksz;
}

/**
 * fastboot_spi_get_part_info() - Lookup SPI partion by name
 *
 * @part_name: Named device to lookup
 * @part_info: Pointer to returned part_info pointer
 * @response: Pointer to fastboot response buffer
 */
int fastboot_spi_get_part_info(const char *part_name,
				struct part_info **part_info, char *response)
{
	struct mtd_info *mtd = NULL;

	return fb_spi_lookup(part_name, &mtd, part_info, response);
}

/**
 * fastboot_spi_flash_write() - Write image to SPI for fastboot
 *
 * @cmd: Named device to write image to
 * @download_buffer: Pointer to image data
 * @download_bytes: Size of image data
 * @response: Pointer to fastboot response buffer
 */
void fastboot_spi_flash_write(const char *cmd, void *download_buffer,
					u32 download_bytes, char *response)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret;

	ret = fb_spi_lookup(cmd, &mtd, &part, response);
	if (ret) {
		pr_err("invalid SPI device");
		fastboot_fail("invalid SPI device", response);
		return;
	}

	ret = board_fastboot_write_partition_setup(part->name);
	if (ret)
		return;

	if (is_sparse_image(download_buffer)) {
		struct fb_spi_sparse sparse_priv;
		struct sparse_storage sparse;

		sparse_priv.mtd = mtd;
		sparse_priv.part = part;

		sparse.blksz = mtd->writesize;
		sparse.start = part->offset / sparse.blksz;
		sparse.size = part->size / sparse.blksz;
		sparse.write = fb_spi_sparse_write;
		sparse.mssg = fastboot_fail;

		printf("Flashing sparse image at offset " LBAFU "\n",
				sparse.start);

		sparse.priv = &sparse_priv;
		ret = write_sparse_image(&sparse, cmd, download_buffer,
					 response);
		if (!ret)
			fastboot_okay(NULL, response);
	} else {
		printf("Flashing raw image at offset 0x%llx\n",
		       part->offset);

		ret = _fb_spi_write(mtd, part, download_buffer, part->offset,
						download_bytes, NULL);

		printf("........ wrote %u bytes to '%s'\n",
				download_bytes, part->name);
	}

	if (ret) {
		fastboot_fail("error writing the image", response);
		return;
	}

	fastboot_okay(NULL, response);
}

/**
 * fastboot_spi_erase() - Erase SPI for fastboot
 *
 * @cmd: Named device to erase
 * @response: Pointer to fastboot response buffer
 */
void fastboot_spi_erase(const char *cmd, char *response)
{
	struct part_info *part;
	struct mtd_info *mtd = NULL;
	int ret;

	ret = fb_spi_lookup(cmd, &mtd, &part, response);
	if (ret) {
		pr_err("invalid SPI device");
		fastboot_fail("invalid SPI device", response);
		return;
	}

	ret = board_fastboot_erase_partition_setup(part->name);
	if (ret)
		return;

	ret = _fb_spi_erase(mtd, part);
	if (ret) {
		pr_err("failed erasing from device %s", mtd->name);
		fastboot_fail("failed erasing from device", response);
		return;
	}

	fastboot_okay(NULL, response);
}
