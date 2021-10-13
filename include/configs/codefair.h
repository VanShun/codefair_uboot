/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 * Configuration settings for the WOKOO SOM Starter Kits.
 */

#ifndef __WOKOO_CODEFAIR_CONFIG_H__
#define __WOKOO_CODEFAIR_CONFIG_H__

#include <linux/sizes.h>
#include <asm/arch-wokoo/wokoo_reg_address.h>

#define CONFIG_BOARD_POSTCLK_INIT
#define CONFIG_MXC_GPT_HCLK

#define CONFIG_SYS_BOOTM_LEN	0x1000000

#include <linux/sizes.h>

#ifndef CONFIG_WOKOO
#define CONFIG_WOKOO
#endif

#define CONFIG_SYS_FSL_CLK

/* ATAGs */
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

/* Boot options */
#if defined(CONFIG_WOKOO)
#define CONFIG_LOADADDR		0x00008000
#else
#define CONFIG_LOADADDR		0x12000000
#endif
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR
#ifdef CONFIG_WOKOO_APP
    #define CONFIG_SYS_MONITOR_LEN  (1024 << 10)
#else
    #ifdef CONFIG_HUSH_PARSER
       #define CONFIG_SYS_MONITOR_LEN  (384 << 10)
     #else
     #define CONFIG_SYS_MONITOR_LEN  (128 << 10)
     #endif
#endif
#define CONFIG_CMD_TIMER

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Miscellaneous configurable options */
#define CONFIG_SYS_CBSIZE	512
#define CONFIG_SYS_MAXARGS	32

/* MMC */

/* Secure boot (HAB) support */
#ifdef CONFIG_SECURE_BOOT
#define CONFIG_CSF_SIZE			0x4000
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT
#endif
#endif

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(1 * SZ_1M)

/* Total Size of Environment Sector */
#define CONFIG_ENV_OFFSET		0x70000
#define CONFIG_ENV_SECT_SIZE	SZ_4K
#define CONFIG_ENV_SIZE			SZ_64K

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#ifdef CONFIG_WOKOO_UART
#define WOKOO_UART_BASE  0xA0144000
#endif

#ifdef CONFIG_WOKOO_SSI
    #define  WOKOO_ROOT_NODE  5
#else
	#define  WOKOO_ROOT_NODE  4
#endif
/* Default environment */
#ifdef CONFIG_WOKOO_MINI
#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"splashpos=m,m\0" \
	"splashimage=" __stringify(CONFIG_LOADADDR) "\0" \
	"image=uImage\0" \
	"fit_image=fit.itb\0" \
	"fdt_high=0xffffffff\0" \
	"fdt_addr=" FDT_ADDR "\0" \
	"boot_fdt=try\0" \
	"spiboot=sf probe $spidev; " \
		"sf read 0x8000 0x100000 0x200000; " \
		"sf read 0x1f00000 0x80000 0x2000; " \
		"bootm 0x8000 - 0x1f00000\0" \
	"bootargs=console=ttyWK0,115200 " \
		"root=/dev/mtdblock4 rw rootfstype=cramfs init=/init " \
		""__stringify(CONFIG_MTDPARTS_DEFAULT) "\0" \

#else
#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"splashpos=m,m\0" \
	"splashimage=" __stringify(CONFIG_LOADADDR) "\0" \
	"image=uImage\0" \
	"fit_image=fit.itb\0" \
	"fdt_high=0xffffffff\0" \
	"fdt_addr=" FDT_ADDR "\0" \
	"boot_fdt=try\0" \
	"spiroot=/dev/mtdblock"__stringify(WOKOO_ROOT_NODE) "\0" \
	"spithread=echo Rthreading from spi flash ...; " \
		"sf probe $spidev; " \
		"sf read 0x8000 0x100000 0x500000; " \
		"go 0x8000\0" \
	"spirtos=echo Rthreading from spi flash ...; " \
		"sf probe $spidev; " \
		"sf read 0x8000 0x100000 0x500000; " \
		"go 0x8000\0" \
	"spiboot=echo Booting from spi flash ...; " \
		"sf probe $spidev; " \
		"sf read 0x8000 0x100000 0x500000; " \
		"sf read 0x1f00000 0x80000 0x8000; " \
		"bootm 0x8000 - 0x1f00000\0" \
	"bootargs=console=ttyWK0,115200 " \
		"root=${spiroot} rw rootfstype=jffs2 init=/sbin/init " \
		""__stringify(CONFIG_MTDPARTS_DEFAULT) "\0" \

#endif

#ifdef CONFIG_HUSH_PARSER
#define CONFIG_BOOTCOMMAND		"run $modeboot"
#else

#define CONFIG_BOOTCOMMAND "run spiboot" 

#endif


/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x00000000
#ifdef CONFIG_WOKOO_DDR3
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)       //128M
#else
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x2000000)       //32M
#endif
#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#ifdef CONFIG_WOKOO
# define DRAM_OFFSET(x)			0x1e##x
# define FDT_ADDR			__stringify(DRAM_OFFSET(00000))
#else 
# define DRAM_OFFSET(x)			0x1##x
# define FDT_ADDR			__stringify(DRAM_OFFSET(8000000))
#endif

/* Physical Memory Map */
#define PHYS_SDRAM			0x00000000

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_SP_OFFSET)

#if CONFIG_USB_DWC2 || CONFIG_USB_GADGET_DWC2_OTG
#define CONFIG_USB_DWC2_REG_ADDR 0xA0300000
#endif

/* Generic Timer Definitions */
#define COUNTER_FREQUENCY		8000000	/* 8MHz */

/* Falcon Mode */
#ifdef CONFIG_SPL_OS_BOOT
# define CONFIG_SPL_FS_LOAD_ARGS_NAME	"args"
# define CONFIG_SPL_FS_LOAD_KERNEL_NAME	"uImage"
# define CONFIG_CMD_SPL
# define CONFIG_SYS_SPL_ARGS_ADDR	0x1800000
# define CONFIG_CMD_SPL_WRITE_SIZE	(64 * SZ_1K)
#endif

#ifdef CONFIG_SPL_BUILD
#define CONFIG_MALLOC_F_ADDR		0x00008000
#endif

/* SPL */

#endif /* __WOKOO_CODEFAIR_CONFIG_H__ */
