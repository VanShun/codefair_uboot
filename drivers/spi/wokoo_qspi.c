/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */
#include <common.h>
#include <console.h>
#include <malloc.h>
#include <spi.h>
#include <wait_bit.h>
#include <asm/arch/wokoo_qspi.h>
#include <asm/arch/wokoo_dma.h>
#include <linux/mtd/spi-nor.h>
#include <asm/io.h>




/*
 * wokoo qspi alave
 *
 * @flags: spi xfer flag
 * @cur_seqid: spi cmd id
 * @sf_addr: spi offset addr
 * @spi_slave: spi slave
 * @wokoo_qspi_regs: qspi regs
 */
struct wokoo_qspi_slave {
	u8  force_quad;
	u32 flags;
	u32 cur_seqid;
	u32 cur_readcmd;
	u32 cur_writecmd;
	u32 sf_addr;
	u32 addr_len;
#ifndef CONFIG_DM_SPI
	struct spi_slave	slave;
#endif
	struct wokoo_qspi_regs	*regs;
};




#define OFFSET_BITS_MASK	GENMASK(23, 0)




static int WOKOO_QSPI_WaitForCompletion(struct wokoo_qspi_regs *regs);
static int WOKOO_QSPI_CMD_Read(struct wokoo_qspi_regs *regs, uint8_t cmd, uint8_t *addr, uint32_t len);
static int WOKOO_QSPI_Wait_Idle(struct wokoo_qspi_regs *regs);
#ifndef CONFIG_DM_SPI
static int WOKOO_QSPI_Wait_Ready(struct wokoo_qspi_regs *regs);
#endif
static int WOKOO_QSPI_DirectQuadOutputInit(struct wokoo_qspi_regs *regs);
static int WOKOO_QSPI_Read(struct wokoo_qspi_regs *regs, uint32_t addr, uint32_t *data, uint32_t count);
static int WOKOO_QSPI_CMD_Write(struct wokoo_qspi_regs *regs, uint8_t cmd,
								 uint32_t addr, uint8_t bytes, uint8_t *buf, uint32_t len);




/*
 * WOKOO_QSPI_WaitForCompletion - wait completion
 *
 * @regs: regs
 */
static int WOKOO_QSPI_WaitForCompletion(struct wokoo_qspi_regs *regs) {
	int timeout;
	int i;

	timeout = 10000;
	for (i = timeout; i > 0; i--) {
		if ((readl(&regs->FCR) & QSPI_FCR_COMMAND_EXECUTE_IN_PROGRESS) == 0) {
			break;
		}
		
	}
	if (i == 0) {
		return (-1);
	}
	return (0);
}

/*
 * WOKOO_QSPI_Wait_Idle - wait idle
 *
 * @regs: regs
 */
static int WOKOO_QSPI_Wait_Idle(struct wokoo_qspi_regs *regs) {
	uint32_t regv;

	do {
		regv = readl(&regs->CFG);
		if (regv & QSPI_CFG_STATUS_IDLE) {
			break;
		}
	} while (1);

	return (0);
}

/*
 * WOKOO_QSPI_CMD_Read - read command
 *
 * @regs: regs
 * @cmd: command
 * @addr: buffer
 * @len: buffer length
 */
static int WOKOO_QSPI_CMD_Read(struct wokoo_qspi_regs *regs, uint8_t cmd, uint8_t *buf, uint32_t len) {
	uint32_t data;
	uint32_t reg;
	int ret;
	int i, j;

	WOKOO_QSPI_Wait_Idle(regs);
	reg = (cmd << QSPI_FCR_COMMAND_OPCODE_POS);
	if (len > 0) {
		reg |= ((len - 1) << QSPI_FCR_READ_DATA_BYTES_POS);
		reg |= QSPI_FCR_READ_DATA_ENABLE;
	}
	writel(reg, &regs->FCR);

	reg |= QSPI_FCR_EXECUTE_THE_COMMAND;
	writel(reg, &regs->FCR);

	ret = WOKOO_QSPI_WaitForCompletion(regs);
	if (ret != 0) {
		return (ret);
	}

	if (len > 4) {
		j = 4;
	} if (len > 8) {
		j   = 4;
		len = 8;
	} else {
		j = len;
	}

	if (j) {
		/* Lower bytes */
		data = readl(&regs->FCRDRL);
		for (i = 0; i < j; i++) {
			buf[i] = (data >> (i * 8)) & 0xff;
		}
	}

	/* Upper bytes */
	if (len > 4) {
		data = readl(&regs->FCRDRU);
		for (i = 4; i < len; i++) {
			buf[i] = (data >> ((i - 4) * 8)) & 0xff;
		}
	}
	return (0);
}

/*
 * WOKOO_QSPI_CMD_Write - write command
 *
 * @regs: regs
 * @cmd: command
 * @addr: address
 * @bytes: address bytes
 * @addr: buffer
 * @len: buffer length
 */
static int  WOKOO_QSPI_CMD_Write(struct wokoo_qspi_regs *regs, uint8_t cmd,
								 uint32_t addr, uint8_t bytes, uint8_t *buf, uint32_t len) {
	uint32_t reg = 0;
	uint32_t data_rl = 0;
	uint32_t data_ru = 0;
	uint32_t nl, nu, i;
	int ret;

	WOKOO_QSPI_Wait_Idle(regs);
	if (len > 8) {
		len = 8;
	}

	if (len < 4) {
		nu = 0;
		nl = len;
	} else {
		nl = 4;
		nu = len - nl;
	}

	/* Lower bytes */
	if (nl) {
		for (i = 0; i < nl; i++) {
			data_rl |= buf[i] << i * 8;
		}

		writel(data_rl, &regs->FCWDRL);
	}

	/* Upper bytes */
	if (nu) {
		for (i = 0; i < nu; i++) {
			data_ru |= buf[i + 4] << i * 8;
		}

		writel(data_ru, &regs->FCWDRU);
	}

	reg = (cmd << QSPI_FCR_COMMAND_OPCODE_POS);
	if (bytes > 0) {
		writel(addr, &regs->FCAR);
		reg |= QSPI_FCR_COMMAND_ADDRESS_ENABLE;
		reg |= ((bytes - 1) << QSPI_FCR_ADDRESS_BYTES_POS);
	}

	if (len > 0) {
		reg |= QSPI_FCR_WRITE_DATA_ENABLE;
		reg |= ((len - 1) << QSPI_FCR_WRITE_DATA_BYTES_POS);
	}
	writel(reg, &regs->FCR);
	reg |= QSPI_FCR_EXECUTE_THE_COMMAND;
	writel(reg, &regs->FCR);
	ret = WOKOO_QSPI_WaitForCompletion(regs);
	WOKOO_QSPI_Wait_Idle(regs);

	return (ret);
}

#ifndef CONFIG_DM_SPI
/*
 * WOKOO_QSPI_Wait_Ready - wait ready
 *
 * @regs: regs
 */
static int WOKOO_QSPI_Wait_Ready(struct wokoo_qspi_regs *regs) {
	uint8_t data = 0;
	int     ret  = 0;

	do {
		ret = WOKOO_QSPI_CMD_Read(regs, QSPI_CMD_READ_STATUS, &data, 1);
	
	} while (data & QSPI_STATUS_WIP);

	return ret;
}
#endif

/*
 * WOKOO_QSPI_DirectQuadOutputInit - qspi init
 *
 * @regs: regs
 */
static int WOKOO_QSPI_DirectQuadOutputInit(struct wokoo_qspi_regs *regs) {
	uint32_t reg;
	int ret = 0;

	reg  = readl(&regs->CFG);
	reg &= ~QSPI_CFG_ENABLE;
	reg &= ~QSPI_CFG_MMBRD_MSK;
	reg |= (0x1 << QSPI_CFG_MMBRD_POS);
	writel(reg, &regs->CFG);
	writel(0, &regs->IMR);

	reg = (0 << QSPI_DELAY_CSDA_POS);
	reg |= (0 << QSPI_DELAY_CSDADS_POS);
	reg |= (0 << QSPI_DELAY_CSEOT_POS);
	reg |= (0 << QSPI_DELAY_CSSOT_POS);
	writel(reg, &regs->DELAY);

	reg = readl(&regs->RDDATACAP);
	reg &= ~(QSPI_RDDATACAP_DELAY_READ_MSK);
	reg |= (0x1 << QSPI_RDDATACAP_DELAY_READ_POS);
	writel(reg, &regs->RDDATACAP);

	writel(readl(&regs->CFG) | QSPI_CFG_ENABLE, &regs->CFG);
	WOKOO_QSPI_Wait_Idle(regs);

	writel(readl(&regs->CFG) | QSPI_CFG_EAARMAP, &regs->CFG);
	WOKOO_QSPI_Wait_Idle(regs);

    return ret;
}

/*
 * WOKOO_QSPI_Write - qspi write data
 *
 * @regs: regs
 * @addr: offset address
 * @data: data buffer
 * @count: data length
 */
static int WOKOO_QSPI_Write(struct wokoo_qspi_regs *regs, uint32_t addr, uint32_t *data, uint32_t count) {
	uint32_t s;
	uint32_t *p;

	WOKOO_QSPI_Wait_Idle(regs);
	writel(addr, &regs->REMAPADDR);

	p = (uint32_t *) WOKOO_QSPI_MAP_ADDR;
	for (s = 0; s < count; s = s + 1)
		*p++ = data[s];

	WOKOO_QSPI_Wait_Idle(regs);
	return (0);
}

/*
 * WOKOO_QSPI_Read - qspi read data
 *
 * @regs: regs
 * @addr: offset address
 * @data: data buffer
 * @count: data length
 */
static int WOKOO_QSPI_Read(struct wokoo_qspi_regs *regs, uint32_t addr, uint32_t *data, uint32_t count) {
	uint32_t s;
	uint32_t *p;

	WOKOO_QSPI_Wait_Idle(regs);
	writel(addr, &regs->REMAPADDR);

	p = (uint32_t *) WOKOO_QSPI_MAP_ADDR;
	for (s = 0; s < count; s = s + 1) {
		data[s] = *p++;
	}

	return (0);
}

/*
 * WOKOO_QSPI_DMA_Read - qspi dma read data
 *
 * @regs: regs
 * @addr: offset address
 * @data: data buffer
 * @count: data length
 */
static int WOKOO_QSPI_DMA_Read(struct wokoo_qspi_regs *regs, uint32_t addr, uint32_t *data, uint32_t count) {
	int dma_err = -1;
	uint32_t remain;
	dma_config_t config;

	WOKOO_QSPI_Wait_Idle(regs);
	writel(addr, &regs->REMAPADDR);

	config.dst = (void *)data;
	config.src = (void *)WOKOO_QSPI_MAP_ADDR;
	config.dst_space = 0;
	config.src_space = 0;

	dma_reset(0);
	remain = dma_calc_transfer_size(count << 2, &config);
	dma_transfer(0, &config);

	while (!dma_is_transfer_end(0)) {
		if (dma_status_is_err(0)) {
			dma_reset(0);
			return dma_err;
		}
	}

	dma_clear_transfer_end(0);
	if (remain) {
		config.dst = (void *)(data + config.x_size * config.y_size);
		dma_calc_transfer_size(remain, &config);
		dma_transfer(0, &config);

		while (!dma_is_transfer_end(0)) {
			if (dma_status_is_err(0)) {
				dma_reset(0);
				return dma_err;
			}
		}

		dma_clear_transfer_end(0);
	}

	return 0;
}

/*
 * wokoo_qspi_init - qspi init
 *
 * @regs: regs
 */
static void wokoo_qspi_init(struct wokoo_qspi_regs *regs)
{
	WOKOO_QSPI_DirectQuadOutputInit(regs);
}

/*
 * qspi_op_write_init - qspi write init
 *
 * @priv: slave
 */
static void qspi_op_write_init(struct wokoo_qspi_slave *priv)
{
	u32 reg;

	if (priv->cur_seqid != priv->cur_writecmd) {
		/* Set register only in idle status */
		WOKOO_QSPI_Wait_Idle(priv->regs);
		reg = readl(&priv->regs->DEVSZ) & ~QSPI_DEVSZ_ADDRESS_BYTES_MSK;
		reg |= (priv->addr_len - 1);
		writel(reg, &priv->regs->DEVSZ);
		reg = 0;

		priv->cur_writecmd = priv->cur_seqid;
		if (priv->cur_seqid == SPINOR_OP_PP_1_1_4 ||
			priv->cur_seqid == SPINOR_OP_PP_1_4_4 ||
			priv->cur_seqid == SPINOR_OP_PP_1_1_4_4B ||
			priv->cur_seqid == SPINOR_OP_PP_1_4_4_4B) {
			reg |= (0x02 << QSPI_DEVWR_DATA_TRANSFER_TYPE_POS);
			if (priv->cur_seqid == SPINOR_OP_PP_1_4_4 ||
				priv->cur_seqid == SPINOR_OP_PP_1_4_4_4B) {
				/* Extend Quad Page Program */
				reg |= (0x02 << QSPI_DEVWR_ADDRESS_TRANSFER_TYPE_POS);
			}
		} else {
			if (priv->force_quad) {
				reg |= (0x02 << QSPI_DEVWR_DATA_TRANSFER_TYPE_POS);
				if (priv->addr_len == 4) {
					priv->cur_seqid = SPINOR_OP_PP_1_1_4_4B;
				} else if (priv->addr_len == 3) {
					priv->cur_seqid = SPINOR_OP_PP_1_1_4;
				}
			} else {
				if (priv->cur_seqid == SPINOR_OP_PP ||
					priv->cur_seqid == SPINOR_OP_PP_4B) {
					reg |= (0x00 << QSPI_DEVWR_DATA_TRANSFER_TYPE_POS);
				}
			}
		}

		reg |= (0x00 << QSPI_DEVWR_WRITE_INSTRUCTION_POS);
		reg |= (priv->cur_seqid << QSPI_DEVWR_WRITE_OPCODE_POS);
		writel(reg, &priv->regs->DEVWR);
	}
}

/*
 * qspi_op_write - qspi write
 *
 * @priv: slave
 * @txbuf: tranfser buffer
 * @len: length
 */
static void qspi_op_write(struct wokoo_qspi_slave *priv, uint8_t *txbuf, u32 len)
{
	u32 nquad, ntail, tail, i;
	u8 *tdata;

	nquad = len / 4;
	ntail = len % 4;

	if (txbuf != NULL) {
		qspi_op_write_init(priv);

		if (nquad) {
			WOKOO_QSPI_Write(priv->regs, priv->sf_addr, (uint32_t *)txbuf, nquad);
		}

		if (ntail) {
			tail  = 0;
			tdata = txbuf + 4 * nquad;
			for (i = 0; i < ntail; i++) {
				tail |= (*(tdata + i) << (i * 8));
			}

			for (; i < 4; i++) {
				tail |= 0xff << (i * 8);
			}

			WOKOO_QSPI_Write(priv->regs, priv->sf_addr + nquad * 4, &tail, 1);
		}
	}
}

/*
 * qspi_op_read_init - qspi read init
 *
 * @priv: slave
 */
static void qspi_op_read_init(struct wokoo_qspi_slave *priv)
{
	u32 reg;

	if (priv->cur_seqid != priv->cur_readcmd) {
		/* Set register only in idle status */
		WOKOO_QSPI_Wait_Idle(priv->regs);
		/* Write address length */
		reg = readl(&priv->regs->DEVSZ) & ~QSPI_DEVSZ_ADDRESS_BYTES_MSK;
		reg |= (priv->addr_len - 1);
		writel(reg, &priv->regs->DEVSZ);
		reg = 0;
		priv->cur_readcmd = priv->cur_seqid;

		if (priv->cur_seqid == SPINOR_OP_READ_1_1_4 ||
			priv->cur_seqid == SPINOR_OP_READ_1_4_4 ||
			priv->cur_seqid == SPINOR_OP_READ_1_1_4_4B ||
			priv->cur_seqid == SPINOR_OP_READ_1_4_4_4B) {
			if (priv->cur_seqid == SPINOR_OP_READ_1_4_4 ||
				priv->cur_seqid == SPINOR_OP_READ_1_4_4_4B) {
				/* Quad I/O Fast Read£¬ 3B or 4B address */
				reg = (0x06 << QSPI_DEVRD_READ_INSTRUCTION_POS);
				reg |= (0x02 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
			} else {
				/* Quad Output Fast Read */
				reg = (0x08 << QSPI_DEVRD_READ_INSTRUCTION_POS);
				reg |= (0x00 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
			}
			reg |= (0x02 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
		} else {
			if (priv->force_quad) {
				/* Quad Output Fast Read */
				reg  = (0x08 << QSPI_DEVRD_READ_INSTRUCTION_POS);
				reg |= (0x02 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
				reg |= (0x00 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
				if (priv->addr_len == 4) {
					priv->cur_seqid = SPINOR_OP_READ_1_1_4_4B;
				} else if (priv->addr_len == 3) {
					priv->cur_seqid = SPINOR_OP_READ_1_1_4;
				}
			} else {
				if (priv->cur_seqid == SPINOR_OP_READ_FAST ||
					priv->cur_seqid == SPINOR_OP_READ ||
					priv->cur_seqid == SPINOR_OP_READ_FAST_4B ||
					priv->cur_seqid == SPINOR_OP_READ_4B) {
					/* Read Data Bytes or Fast Read */
					reg  = (0x08 << QSPI_DEVRD_READ_INSTRUCTION_POS);
					reg |= (0x00 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
					reg |= (0x00 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
				} else if (priv->cur_seqid == SPINOR_OP_READ_1_1_2 ||
					   priv->cur_seqid == SPINOR_OP_READ_1_2_2 ||
					   priv->cur_seqid == SPINOR_OP_READ_1_1_2_4B ||
					   priv->cur_seqid == SPINOR_OP_READ_1_2_2_4B ) {
					if (priv->cur_seqid == SPINOR_OP_READ_1_2_2 ||
						priv->cur_seqid == SPINOR_OP_READ_1_2_2_4B) {
						/* Dual I/O Fast Read */
						reg  = (0x04 << QSPI_DEVRD_READ_INSTRUCTION_POS);
						reg |= (0x01 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
					} else {
						/* Dual Output Fast Read */
						reg  = (0x14 << QSPI_DEVRD_READ_INSTRUCTION_POS);
						reg |= (0x01 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
					}
					reg |= (0x01 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
				} else {
					/* Other command, like 0x5A etc */
					reg  = (0x08 << QSPI_DEVRD_READ_INSTRUCTION_POS);
					reg |= (0x00 << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS);
					reg |= (0x00 << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS);
				}
			}
		}

		reg |= (0x00 << QSPI_DEVRD_INSTRUCTION_TYPE_POS);
		reg |= (priv->cur_seqid << QSPI_DEVRD_READ_OPCODE_POS);
		writel(reg, &priv->regs->DEVRD);
	}
}

/*
 * qspi_op_read - qspi read
 *
 * @priv: slave
 * @rxbuf: tranfser buffer
 * @len: length
 */
static void qspi_op_read(struct wokoo_qspi_slave *priv, uint8_t *rxbuf, u32 len)
{
	u32 nquad, ntail, tail, i;
	u8 *rdata;

	nquad = len / 4;
	ntail = len % 4;

	if (rxbuf != NULL) {
		qspi_op_read_init(priv);
		if (nquad != 0) {
			if (WOKOO_QSPI_DMA_Read(priv->regs, priv->sf_addr, (uint32_t *)rxbuf, nquad)) {
				WOKOO_QSPI_Read(priv->regs, priv->sf_addr, (uint32_t *)rxbuf, nquad);
			}
		}

		if (ntail) {
			rdata = rxbuf + 4 * nquad;
			WOKOO_QSPI_Read(priv->regs, priv->sf_addr + nquad * 4, &tail, 1);
			for (i = 0; i < ntail; i++) {
				*(rdata + i) = (tail & (0xff << (i * 8))) >> (8 * i);
			}
		}
	}
}

int wokoo_qspi_xfer_common(struct wokoo_qspi_slave *priv, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	u32 bytes = bitlen / 8;
	u32 txbuf;

	WATCHDOG_RESET();

	if (dout) {
		if (flags & SPI_XFER_BEGIN) {
			priv->cur_seqid = *(u8 *)dout;
			priv->addr_len  = bytes - 1;
			memcpy(&txbuf, dout + 1, 4);
			priv->sf_addr = txbuf;
		}

		if (flags & SPI_XFER_END) {
			if (flags & SPI_XFER_BEGIN) {
				bytes = 0;
			}

			if (priv->addr_len == 3) {
				priv->sf_addr = swab32(priv->sf_addr) >> 8;
				priv->addr_len = 3;
			} else if (priv->addr_len == 4) {
				priv->sf_addr = swab32(priv->sf_addr);
				priv->addr_len = 4;
			} else {
				priv->addr_len = 0;
				priv->sf_addr  = 0;
			}

			if (priv->addr_len) {
				if (bytes) {
					qspi_op_write(priv, (uint8_t *)dout, bytes);
				} else {
					WOKOO_QSPI_CMD_Write(priv->regs, priv->cur_seqid, priv->sf_addr, priv->addr_len, (uint8_t *)dout, bytes);
				}
			} else {
				WOKOO_QSPI_CMD_Write(priv->regs, priv->cur_seqid, 0, 0, (uint8_t *)dout, bytes);
			}
		}
	}

	if (din) {
		if (flags & SPI_XFER_END) {
			/* One byte is read dummy data size, three/four byte is address length */
			if (priv->addr_len == 4) {
				priv->sf_addr = swab32(priv->sf_addr) >> 8;
				priv->addr_len = 3;
			} else if (priv->addr_len == 5) {
				priv->sf_addr = swab32(priv->sf_addr);
				priv->addr_len = 4;
			} else {
				priv->addr_len = 0;
				priv->sf_addr  = 0;
			}

			if (bytes && priv->addr_len) {
				qspi_op_read(priv, din, bytes);
			} else {
				WOKOO_QSPI_CMD_Read(priv->regs, priv->cur_seqid, (uint8_t *)din, bytes);
			}
		}
	}

	return 0;
}

#ifndef CONFIG_DM_SPI
static inline struct wokoo_qspi_slave *to_wokoo_qspi(struct spi_slave *slave)
{
	return container_of(slave, struct wokoo_qspi_slave, slave);
}

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return 1;
}

static void wokoo_qspi_cs_activate(void)
{
	/* Enable SPI Function */
}

static void wokoo_qspi_cs_deactivate(void)
{
	/* Disable SPI Function */
}

void spi_cs_activate(struct spi_slave *slave)
{
	wokoo_qspi_cs_activate();
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	wokoo_qspi_cs_deactivate();
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int mode)
{
	struct wokoo_qspi_slave *ss;

	if (!spi_cs_is_valid(bus, cs))
		return NULL;

	ss = spi_alloc_slave(struct wokoo_qspi_slave, bus, cs);
	if (!ss) {
		printf("SPI_error: Fail to allocate wokoo_qspi_slave\n");
		return NULL;
	}

	/* Init WOKOO QSPI */
	ss->force_quad = 1;
	ss->regs = (struct wokoo_qspi_regs *)WOKOO_QSPI_BASE_ADDR;
	wokoo_qspi_init(ss->regs);
	if (ss->force_quad == 1) {
		uint8_t wvalue;
		/* Enable quad spi for flash, just for QE(S9) = 1 */
		WOKOO_QSPI_Wait_Ready(ss->regs);

		WOKOO_QSPI_CMD_Write(ss->regs, QSPI_CMD_WRITE_ENABLE, 0, 0, NULL, 0);
		WOKOO_QSPI_Wait_Idle(ss->regs);
		WOKOO_QSPI_Wait_Ready(ss->regs);
		WOKOO_QSPI_Wait_Idle(ss->regs);

		wvalue = 0x2;
		WOKOO_QSPI_CMD_Write(ss->regs, 0x31, 0, 0, &wvalue, 1);
		WOKOO_QSPI_Wait_Idle(ss->regs);
		WOKOO_QSPI_Wait_Ready(ss->regs);
		WOKOO_QSPI_Wait_Idle(ss->regs);
	}

	return &ss->slave;
}

void spi_free_slave(struct spi_slave *slave)
{
	struct wokoo_qspi_slave *spi = to_wokoo_qspi(slave);

	free(spi);
}

int spi_claim_bus(struct spi_slave *slave)
{
	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
}

int spi_xfer(struct spi_slave *slave, unsigned int bitlen,
			const void *dout, void *din, unsigned long flags)
{
	struct wokoo_qspi_slave *ss = to_wokoo_qspi(slave);

	return wokoo_qspi_xfer_common(ss, bitlen, dout, din, flags);
}

#else

#include <dm.h>

static int wokoo_qspi_xfer(struct udevice *dev, unsigned int bitlen,
			const void *dout, void *din, unsigned long flags)
{
	struct udevice *bus = dev->parent;
	struct wokoo_qspi_slave *ss = dev_get_platdata(bus);

	return wokoo_qspi_xfer_common(ss, bitlen, dout, din, flags);
}

static int wokoo_qspi_set_speed(struct udevice *dev, uint speed)
{
	/* This is a SPI NOR controller, do nothing. */
	return 0;
}

static int wokoo_qspi_set_mode(struct udevice *dev, uint mode)
{
	/* This is a SPI NOR controller, do nothing. */
	return 0;
}

static int wokoo_qspi_probe(struct udevice *dev)
{
	struct wokoo_qspi_slave *ss = dev_get_platdata(dev);

	wokoo_qspi_init(ss->regs);
#if 0
	ss->force_quad = 1;
	if (ss->force_quad == 1) {
		uint8_t wvalue;
		/* Enable quad spi for flash, just for QE(S9) = 1 */
		WOKOO_QSPI_Wait_Ready(ss->regs);

		WOKOO_QSPI_CMD_Write(ss->regs, QSPI_CMD_WRITE_ENABLE, 0, 0, NULL, 0);
		WOKOO_QSPI_Wait_Idle(ss->regs);
		WOKOO_QSPI_Wait_Ready(ss->regs);
		WOKOO_QSPI_Wait_Idle(ss->regs);

		wvalue = 0x2;
		WOKOO_QSPI_CMD_Write(ss->regs, 0x31, 0, 0, &wvalue, 1);
		WOKOO_QSPI_Wait_Idle(ss->regs);
		WOKOO_QSPI_Wait_Ready(ss->regs);
		WOKOO_QSPI_Wait_Idle(ss->regs);
	}
#endif
	return 0;
}

static int wokoo_qspi_ofdata_to_platdata(struct udevice *bus)
{
	struct wokoo_qspi_slave *ss = bus->platdata;
	const void *blob = gd->fdt_blob;
	int node = dev_of_offset(bus);

	ss->regs = (struct wokoo_qspi_regs *)fdtdec_get_addr(blob,
								node, "reg");

	return 0;
}

static const struct dm_spi_ops wokoo_qspi_ops = {
	.xfer		= wokoo_qspi_xfer,
	.set_speed	= wokoo_qspi_set_speed,
	.set_mode	= wokoo_qspi_set_mode,
};

static const struct udevice_id wokoo_qspi_ids[] = {
	{ .compatible = "wokoo,wokoo-qspi" },
	{ }
};

U_BOOT_DRIVER(wokoo_qspi) = {
	.name		= "wokoo-qspi",
	.id		= UCLASS_SPI,
	.of_match	= wokoo_qspi_ids,
	.ops		= &wokoo_qspi_ops,
	.ofdata_to_platdata = wokoo_qspi_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct wokoo_qspi_slave),
	.probe		= wokoo_qspi_probe,
	.flags		= DM_FLAG_PRE_RELOC,
};
#endif
