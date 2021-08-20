// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com
 *
 */

#include <common.h>
#include <console.h>
#include <malloc.h>
#include <spi.h>
#include <wait_bit.h>
#include <asm/arch/clock.h>
#include <asm/arch/wokoo_ssi.h>
#include <linux/mtd/spi-nor.h>
#include <asm/io.h>




/*
 * wokoo ssi alave
 *
 * @flags: ssi xfer flag
 * @cur_seqid: ssi cmd id
 * @sf_addr: ssi offset addr
 * @spi_slave: ssi slave
 * @wokoo_ssi_regs: ssi regs
 */
struct wokoo_ssi_slave {
	u32 flags;
	u32 cur_seqid;
	u32 sf_addr;
	u32 cs;
	u32 baud;
	u32 mode;
	u32 max_hz;
#ifndef CONFIG_DM_SPI
	struct spi_slave	slave;
#endif
	struct wokoo_ssi_regs	*regs;
};




static void wokoo_ssi_read_st(struct wokoo_ssi_regs *regs, u8 cmd, u8 *rxbuf);




/*
 * wokoo_ssi_wait - wait completion
 *
 * @regs: regs
 */
static void wokoo_ssi_wait(struct wokoo_ssi_regs *regs)
{
	/* Is SSI0 idle */
	while ((readl(&regs->STS) & WOKOO_SSI0_STS_BUSY) == WOKOO_SSI0_STS_BUSY);
}

#if 0
static void wokoo_ssi_wait_prograss(struct wokoo_ssi_regs *regs)
{
	uint8_t reg_val;

	wokoo_ssi_read_st(regs, &reg_val);
	/* WIP Bit of Flash */
	while ((reg_val & 0x01) == 0x01) {
		wokoo_ssi_read_st(regs, &reg_val);
	}
}
#endif

/*
 * wokoo_ssi_reg_init - ssi0 init
 *
 * @regs: regs
 */
static void wokoo_ssi_reg_init(struct wokoo_ssi_regs *regs, uint32_t baud, uint32_t cs)
{
	uint32_t reg_val;

	/* Disable SSI0 */
	writel(0, &regs->EN);
	/* Disable all interrupt */
	writel(0, &regs->IE);
	reg_val = readl(&regs->CTRL0);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	writel(reg_val, &regs->CTRL0);
	/* SSI0 clk = SSI0_mclk / SCKDV = 3.2M, SCKDV must be even */
	writel(baud, &regs->BAUD);
	/* TX FIFO */
	writel(0, &regs->TXFTL);
	/* RX FIFO */
	writel(0, &regs->RXFTL);
	/* Select slave device cs */
	writel(cs, &regs->SE);
	reg_val = readl(&regs->CTRL0);
	reg_val &= ~WOKOO_SSI0_CTRL0_TMOD_MSK;
	reg_val |= WOKOO_SSI0_CTRL0_TMOD_ROM_RD;
	writel(reg_val, &regs->CTRL0);
	/* Enable SSI0 */
	writel(1, &regs->EN);

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_read_flash_id - ssi0 read flash id
 *
 * @regs: regs
 */
static void wokoo_ssi_read_flash_id(struct wokoo_ssi_regs *regs, u8 *rxbuf, u32 len)
{
	uint32_t reg_val;
	uint32_t i = 0;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_ROM_RD + (0 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val &= ~WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	/* Number of read data frame, 2(N) + 1 = 3 */
	writel(0x2, &regs->CTRL1);
	writel(1, &regs->EN);

	/* Wait for transfer */
	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	/* Reveice FIFO size, when >= set size then trigger interrupt */
	writel(0x2, &regs->RXFTL);
	/* Write read id command */
	writel(SPINOR_OP_RDID, &regs->DATA);

	/* Reveice 3 Byte id value */
	while (1) {
		reg_val = readl(&regs->RIS);
		if (reg_val & WOKOO_SSI0_RIS_RXFIR)	{
			rxbuf[i++] = readl(&regs->DATA);
			rxbuf[i++] = readl(&regs->DATA);
			rxbuf[i++] = readl(&regs->DATA);
			break;
		}
	}

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_read_st - ssi0 read flash status
 *
 * @regs: regs
 * @rxbuf : status buffer
 */
static void wokoo_ssi_read_st(struct wokoo_ssi_regs *regs, u8 cmd, u8 *rxbuf)
{
	uint32_t reg_val;
	int      read_cnt;

	read_cnt = 1;
	/* Disable SSI0 */
	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_ROM_RD + (7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(read_cnt, &regs->CTRL1);
	writel(1, &regs->EN);
	/* Just only reveice one data */
	writel(read_cnt - 1, &regs->RXFTL);

	writel(cmd, &regs->DATA);

	while ((readl(&regs->RIS) & (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR)) 
			   != (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR));

	*rxbuf = readl(&regs->DATA);
	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_write_en - ssi0 flash write enable
 *
 * @regs: regs
 */
static void wokoo_ssi_write_en(struct wokoo_ssi_regs *regs)
{
	uint32_t reg_val;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TXRX + (0 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val &= ~WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(SPINOR_OP_WREN, &regs->DATA);
	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_write_dis - ssi0 flash write disable
 *
 * @regs: regs
 */
static void wokoo_ssi_write_dis(struct wokoo_ssi_regs *regs)
{
	uint32_t reg_val;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TXRX + (0 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val &= ~WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);
	writel(SPINOR_OP_WRDI, &regs->DATA);
	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_write_status - ssi0 flash write status
 *
 * @regs: regs
 * @txbuf: status buffer
 */
static void wokoo_ssi_write_status(struct wokoo_ssi_regs *regs, u8 *txbuf)
{
	uint32_t reg_val;
	int      write_cnt;

	write_cnt = 1;
	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);
	writel(write_cnt, &regs->TXFTL);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(*txbuf++, &regs->DATA);

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_read - ssi0 flash read data
 *
 * @regs: regs
 * @addr: read offset address
 * @rxbuf: read buffer
 * @len: read length
 */
static void wokoo_ssi_read(struct wokoo_ssi_regs *regs, u32 addr, u8 *rxbuf, int len)
{
	int      read_cnt;
	uint32_t reg_val;
	uint32_t read_addr;
	int      i;
	unsigned char addr_div[4];

	read_cnt  = len;
	read_addr = addr;

	while (read_cnt) {
		int one_len;

		/* Reveice FIFO threshold, max value is 16 */
		if (read_cnt > 1024)
			one_len = 1024;
		else
			one_len = read_cnt;

		addr_div[2] = (read_addr & 0x000000FF);
		addr_div[1] = (read_addr & 0x0000FF00) >> 8 ;
		addr_div[0] = (read_addr & 0x00FF0000) >> 16;
		writel(0, &regs->EN);
		reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_ROM_RD + (7 << WOKOO_SSI0_CTRL0_CFS_POS);
		reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
		reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
		reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
		reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
		writel(reg_val, &regs->CTRL0);
		writel(one_len - 1, &regs->CTRL1);
		writel(1, &regs->EN);
		writel(0, &regs->RXFTL);

		/* Write command */
		writel(SPINOR_OP_READ, &regs->DATA);
		/* Write address */
		for  (i = 0; i < 3; i++)
			writel(addr_div[i], &regs->DATA);

		while ((readl(&regs->RIS) & (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR)) 
			   != (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR));

		for (i = 0; i < one_len; i++) {
			while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_RXFIR) != WOKOO_SSI0_RIS_RXFIR);
			*rxbuf++ = readl(&regs->DATA);
		}

		wokoo_ssi_wait(regs);
		read_cnt  -= one_len;
		read_addr += one_len;
	}

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_addr4b_read - ssi0 flash read data
 *
 * @regs: regs
 * @addr: read offset address
 * @rxbuf: read buffer
 * @len: read length
 */
static void wokoo_ssi_addr4b_read(struct wokoo_ssi_regs *regs, u32 addr, u8 *rxbuf, int len)
{
	int      read_cnt;
	uint32_t reg_val;
	uint32_t read_addr;
	int      i;
	unsigned char addr_div[4];

	read_cnt  = len;
	read_addr = addr;

	while (read_cnt) {
		int one_len;

		/* Reveice FIFO threshold, max value is 16 */
		if (read_cnt > 1024)
			one_len = 1024;
		else
			one_len = read_cnt;

		addr_div[3] = (read_addr & 0x000000FF);
		addr_div[2] = (read_addr & 0x0000FF00) >> 8 ;
		addr_div[1] = (read_addr & 0x00FF0000) >> 16;
		addr_div[0] = (read_addr & 0xFF000000) >> 24;
		writel(0, &regs->EN);
		reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_ROM_RD + (7 << WOKOO_SSI0_CTRL0_CFS_POS);
		reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
		reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
		reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
		reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
		writel(reg_val, &regs->CTRL0);
		writel(one_len - 1, &regs->CTRL1);
		writel(1, &regs->EN);
		writel(0, &regs->RXFTL);

		/* Write command */
		writel(SPINOR_OP_READ_4B, &regs->DATA);
		/* Write address */
		for (i = 0; i < 4; i++)
			writel(addr_div[i], &regs->DATA);

		while ((readl(&regs->RIS) & (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR)) 
			   != (WOKOO_SSI0_RIS_TXEIR | WOKOO_SSI0_RIS_RXFIR));

		for (i = 0; i < one_len; i++) {
			while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_RXFIR) != WOKOO_SSI0_RIS_RXFIR);
			*rxbuf++ = readl(&regs->DATA);
		}

		wokoo_ssi_wait(regs);
		read_cnt  -= one_len;
		read_addr += one_len;
	}

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_sector_erase - ssi0 flash erase sector
 *
 * @regs: regs
 * @addr: offset address
 */
static void wokoo_ssi_sector_erase(struct wokoo_ssi_regs *regs, u32 addr)
{
	unsigned char addr_div[4];
	uint32_t      reg_val;

	addr_div[2] = (addr & 0x000000FF);
	addr_div[1] = (addr & 0x0000FF00) >> 8 ;
	addr_div[0] = (addr & 0x00FF0000) >> 16;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->TXFTL);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(SPINOR_OP_BE_4K, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_sector_addr4b_erase - ssi0 flash erase sector
 *
 * @regs: regs
 * @addr: offset address
 */
static void wokoo_ssi_sector_addr4b_erase(struct wokoo_ssi_regs *regs, u32 addr)
{
	unsigned char addr_div[4];
	uint32_t      reg_val;

	addr_div[3] = (addr & 0x000000FF);
	addr_div[2] = (addr & 0x0000FF00) >> 8 ;
	addr_div[1] = (addr & 0x00FF0000) >> 16;
	addr_div[0] = (addr & 0xFF000000) >> 24;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->TXFTL);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(SPINOR_OP_BE_4K_4B, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);
	writel(addr_div[3], &regs->DATA);

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_block_erase - ssi0 flash erase block
 *
 * @regs: regs
 * @addr: offset address
 */
static void wokoo_ssi_block_erase(struct wokoo_ssi_regs *regs, u32 addr)
{
	unsigned char addr_div[4];
	uint32_t      reg_val;
//	addr_div[3] = (addr & 0x000000FF);

	addr_div[2] = (addr & 0x000000FF);
	addr_div[1] = (addr & 0x0000FF00) >>8 ;
	addr_div[0] = (addr & 0x00FF0000) >> 16;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(SPINOR_OP_SE, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);
	//writel(addr_div[3], &regs->DATA);

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_block_addr4b_erase - ssi0 flash erase block
 *
 * @regs: regs
 * @addr: offset address
 */
static void wokoo_ssi_block_addr4b_erase(struct wokoo_ssi_regs *regs, u32 addr)
{
	unsigned char addr_div[4];
	uint32_t      reg_val;

	addr_div[3] = (addr & 0x000000FF);
	addr_div[2] = (addr & 0x0000FF00) >> 8 ;
	addr_div[1] = (addr & 0x00FF0000) >> 16;
	addr_div[0] = (addr & 0xFF000000) >> 24;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);

	writel(SPINOR_OP_SE_4B, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);
	writel(addr_div[3], &regs->DATA);

	wokoo_ssi_wait(regs);
}

#if 0
/*
 * wokoo_ssi_erase_all - ssi0 flash erase whole flash
 *
 * @regs: regs
 */
static void wokoo_ssi_erase_all(struct wokoo_ssi_regs *regs)
{
	uint32_t      reg_val;

	wokoo_ssi_write_en(regs);
	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TXRX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val &= ~WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(1, &regs->EN);

	wokoo_ssi_wait(regs);

	writel(0x60, &regs->DATA);

	wokoo_ssi_wait(regs);
}
#endif

/*
 * wokoo_ssi_write_page - ssi0 flash write data
 *
 * @regs: regs
 * @addr: read offset address
 * @txbuf: write buffer
 * @len: read length
 */
static void wokoo_ssi_write_page(struct wokoo_ssi_regs *regs, u32 addr, u8 *txbuf, int len)
{
	int      cnt;
	uint32_t reg_val;
	unsigned char addr_div[4];

	addr_div[2] = (addr & 0x000000FF);
	addr_div[1] = (addr & 0x0000FF00) >> 8 ;
	addr_div[0] = (addr & 0x00FF0000) >> 16;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(0x7, &regs->TXFTL);
	writel(1, &regs->EN);
	writel(1, &regs->RXFTL);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);
	writel(SPINOR_OP_PP, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);

	/* transmit max 8 bytes one loop */
	if (len > 8)
		cnt = 8;
	else
		cnt = len;

	while (len) {
		reg_val = readl(&regs->RIS);
		/* Waitting for TX FIFO empty intr */
		if (reg_val & WOKOO_SSI0_RIS_TXEIR) {
			/* Transmit once */
			int cnt2 = cnt;
			while (cnt2--) {
				writel(*txbuf++, &regs->DATA);
			}

			/* Left bytes for next */
			len -= cnt;
			if (len > 8)
				cnt = 8;
			else
				cnt = len;
		} else
			continue;
	}

	wokoo_ssi_wait(regs);
}

/*
 * wokoo_ssi_addr4b_write_page - ssi0 flash write data
 *
 * @regs: regs
 * @addr: read offset address
 * @txbuf: write buffer
 * @len: read length
 */
static void wokoo_ssi_addr4b_write_page(struct wokoo_ssi_regs *regs, u32 addr, u8 *txbuf, int len)
{
	int      cnt;
	uint32_t reg_val;
	unsigned char addr_div[4];

	addr_div[3] = (addr & 0x000000FF);
	addr_div[2] = (addr & 0x0000FF00) >> 8 ;
	addr_div[1] = (addr & 0x00FF0000) >> 16;
	addr_div[0] = (addr & 0xFF000000) >> 24;

	writel(0, &regs->EN);
	reg_val = (0 << WOKOO_SSI0_CTRL0_DFS_POS) + (SSI0_CTRL0_FRF_MOTOROLA_SPI << WOKOO_SSI0_CTRL0_FRF_POS)
			+ WOKOO_SSI0_CTRL0_TMOD_TX + (0x7 << WOKOO_SSI0_CTRL0_CFS_POS);
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPH;
	reg_val &= ~WOKOO_SSI0_CTRL0_SCPOL;
	reg_val |= WOKOO_SSI0_CTRL0_SLV_OE;
	reg_val &= ~WOKOO_SSI0_CTRL0_SRL;
	writel(reg_val, &regs->CTRL0);
	writel(0x7, &regs->TXFTL);
	writel(1, &regs->EN);
	writel(1, &regs->RXFTL);

	while ((readl(&regs->RIS) & WOKOO_SSI0_RIS_TXEIR) == 0);
	writel(SPINOR_OP_PP_4B, &regs->DATA);
	writel(addr_div[0], &regs->DATA);
	writel(addr_div[1], &regs->DATA);
	writel(addr_div[2], &regs->DATA);
	writel(addr_div[3], &regs->DATA);

	/* transmit max 8 bytes one loop */
	if (len > 8)
		cnt = 8;
	else
		cnt = len;

	while (len) {
		reg_val = readl(&regs->RIS);
		/* Waitting for TX FIFO empty intr */
		if (reg_val & WOKOO_SSI0_RIS_TXEIR) {
			/* Transmit once */
			int cnt2 = cnt;
			while (cnt2--) {
				writel(*txbuf++, &regs->DATA);
			}

			/* Left bytes for next */
			len -= cnt;
			if (len > 8)
				cnt = 8;
			else
				cnt = len;
		} else
			continue;
	}

	wokoo_ssi_wait(regs);
}

int wokoo_ssi_xfer_common(struct wokoo_ssi_slave *priv, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	u32 bytes = bitlen / 8;
	u32 txbuf;

	WATCHDOG_RESET();

	if (dout) {
		if (flags & SPI_XFER_BEGIN) {
			priv->cur_seqid = *(u8 *)dout;
			memcpy(&txbuf, dout, 4);
		}

		if ((flags == SPI_XFER_END) && 
			(priv->cur_seqid == SPINOR_OP_PP)) {
			wokoo_ssi_write_page(priv->regs, priv->sf_addr, (uint8_t *)dout, bytes);
			return 0;
		}

		if ((flags == SPI_XFER_END) && 
			(priv->cur_seqid == SPINOR_OP_PP_4B)) {
			wokoo_ssi_addr4b_write_page(priv->regs, priv->sf_addr << 8, (uint8_t *)dout, bytes);
			return 0;
		}
		
		if (priv->cur_seqid == SPINOR_OP_READ || priv->cur_seqid == SPINOR_OP_READ_FAST) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
		}  else if (priv->cur_seqid == SPINOR_OP_READ_4B || priv->cur_seqid == SPINOR_OP_READ_FAST_4B) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
		} else if (priv->cur_seqid == SPINOR_OP_BE_4K) {
			
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
			wokoo_ssi_sector_erase(priv->regs, priv->sf_addr);
		} else if (priv->cur_seqid == SPINOR_OP_BE_4K_4B) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
				
			wokoo_ssi_sector_addr4b_erase(priv->regs, priv->sf_addr << 8);
		} else if (priv->cur_seqid == SPINOR_OP_SE) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
			wokoo_ssi_block_erase(priv->regs, priv->sf_addr);
		} else if (priv->cur_seqid == SPINOR_OP_SE_4B) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
			wokoo_ssi_block_addr4b_erase(priv->regs, priv->sf_addr << 8);
		} else if (priv->cur_seqid == SPINOR_OP_PP) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
		} else if (priv->cur_seqid == SPINOR_OP_PP_4B) {
			priv->sf_addr = swab32(txbuf) & OFFSET_BITS_MASK;
		} else if (priv->cur_seqid == SPINOR_OP_WREN) {
			wokoo_ssi_write_en(priv->regs);
		} else if (priv->cur_seqid == SPINOR_OP_WRSR) {
			wokoo_ssi_write_status(priv->regs, din);
		} else if (priv->cur_seqid == SPINOR_OP_WRDI) {
			wokoo_ssi_write_dis(priv->regs);
		}
	}

	if (din) {
		if (priv->cur_seqid == SPINOR_OP_READ || priv->cur_seqid == SPINOR_OP_READ_FAST) {
			
			wokoo_ssi_read(priv->regs, priv->sf_addr,  din, bytes);
		} else if (priv->cur_seqid == SPINOR_OP_READ_4B || priv->cur_seqid == SPINOR_OP_READ_FAST_4B) {
		
			wokoo_ssi_addr4b_read(priv->regs, priv->sf_addr << 8,  din, bytes);
		} else if (priv->cur_seqid == SPINOR_OP_RDID) {
			wokoo_ssi_read_flash_id(priv->regs, din, bytes);
		} else if (priv->cur_seqid == SPINOR_OP_RDSR) {
			wokoo_ssi_read_st(priv->regs, SPINOR_OP_RDSR, din);
		} else if (priv->cur_seqid == SPINOR_OP_RDCR) {
			wokoo_ssi_read_st(priv->regs, SPINOR_OP_RDCR, din);
		} else if (priv->cur_seqid == SPINOR_OP_WREN) {
			wokoo_ssi_write_en(priv->regs);
		} else if (priv->cur_seqid == SPINOR_OP_WRSR) {
			/* Disable this command for flash mybe soft protect */
			wokoo_ssi_write_status(priv->regs, din);
		} else if (priv->cur_seqid == SPINOR_OP_WRDI) {
			wokoo_ssi_write_dis(priv->regs);
		}
	}

	return 0;
}

#ifndef CONFIG_DM_SPI
static inline struct wokoo_ssi_slave *to_wokoo_ssi(struct spi_slave *slave)
{
	return container_of(slave, struct wokoo_ssi_slave, slave);
}

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	if (cs > 2) {
		return 0;
	}

	return 1;
}

static void wokoo_ssi_cs_activate(void)
{
	/* Enable SPI Function */
}

static void wokoo_ssi_cs_deactivate(void)
{
	/* Disable SPI Function */
}

void spi_cs_activate(struct spi_slave *slave)
{
	wokoo_ssi_cs_activate();
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	wokoo_ssi_cs_deactivate();
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int mode)
{
	struct wokoo_ssi_slave *ss;
   
	if (!spi_cs_is_valid(bus, cs))
		return NULL;

	if (max_hz > 16000000) {
		return NULL;
	}

	/* Baud must be even */
	if (max_hz % 2) {
		return NULL;
	}

	ss = spi_alloc_slave(struct wokoo_ssi_slave, bus, cs);
	if (!ss) {
		printf("SPI_error: Fail to allocate wokoo_ssi_slave\n");
		return NULL;
	}

	/* Select device cs */
	ss->cs = (0x1 << cs);
	ss->baud = 4000000 / max_hz;
  
	/* Rest ssi0 modules */
	reset_ssi();
	/* bus_mclk musb be set to 1/12 pll_out, and ssi_clk must be 32M */
	set_ssi_clk(32000);
	enable_spi_clk(1, 0);
	/* Set ssi0 protocol to spi */
	set_ssi_protocol_mode(SSI0_CTRL0_FRF_MOTOROLA_SPI);

	/* Init WOKOO SSI */
	ss->regs = (struct wokoo_ssi_regs *)WOKOO_SSI_BASE_ADDR;
	wokoo_ssi_reg_init(ss->regs, ss->baud, ss->cs);




	return &ss->slave;
}

void spi_free_slave(struct spi_slave *slave)
{
	struct wokoo_ssi_slave *spi = to_wokoo_ssi(slave);

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
	struct wokoo_ssi_slave *ss = to_wokoo_ssi(slave);

	return wokoo_ssi_xfer_common(ss, bitlen, dout, din, flags);
}

#else

#include <dm.h>

static int wokoo_ssi_xfer(struct udevice *dev, unsigned int bitlen,
			const void *dout, void *din, unsigned long flags)
{
	struct udevice *bus = dev->parent;
	struct wokoo_ssi_slave *ss = dev_get_platdata(bus);

	return wokoo_ssi_xfer_common(ss, bitlen, dout, din, flags);
}

static int wokoo_ssi_set_speed(struct udevice *dev, uint speed)
{
	return 0;
}

static int wokoo_ssi_set_mode(struct udevice *dev, uint mode)
{
	/* This is a SPI NOR controller, do nothing. */
	return 0;
}

static int wokoo_ssi_child_pre_probe(struct udevice *dev)
{
	struct wokoo_ssi_slave *ss = dev_get_platdata(dev);
	struct dm_spi_slave_platdata *plat = dev_get_parent_platdata(dev);

	ss->cs = plat->cs;
	ss->baud = 32000 / plat->max_hz;

	return 0;
}

static int wokoo_ssi_probe(struct udevice *dev)
{
	struct wokoo_ssi_slave *ss = dev_get_platdata(dev);

	/* Rest ssi0 modules */
	reset_ssi();
	/* bus_mclk musb be set to 1/12 pll_out, and ssi_clk must be 32M */
	set_ssi_clk(32000);
	/* Set ssi0 protocol to spi */
	set_ssi_protocol_mode(SSI0_CTRL0_FRF_MOTOROLA_SPI);
	enable_spi_clk(1, 0);

	/* Baud must be even */
	if (ss->baud % 2) {
		return -1;
	}

	if (ss->baud == 0) {
		ss->baud = 0x4;
	}
	

	/* Init WOKOO SSI */
	wokoo_ssi_reg_init(ss->regs, ss->baud, 0x1 << ss->cs);

	return 0;
}

static int wokoo_ssi_ofdata_to_platdata(struct udevice *bus)
{
	struct wokoo_ssi_slave *ss = bus->platdata;
	const void *blob = gd->fdt_blob;
	int node = dev_of_offset(bus);

	ss->regs = (struct wokoo_ssi_regs *)fdtdec_get_addr(blob,
								node, "reg");

	return 0;
}

static const struct dm_spi_ops wokoo_ssi_ops = {
	.xfer		= wokoo_ssi_xfer,
	.set_speed	= wokoo_ssi_set_speed,
	.set_mode	= wokoo_ssi_set_mode,
};

static const struct udevice_id wokoo_ssi_ids[] = {
	{ .compatible = "wokoo,wokoo-ssi" },
	{ }
};

U_BOOT_DRIVER(wokoo_ssi) = {
	.name		= "wokoo-ssi",
	.id			= UCLASS_SPI,
	.of_match	= wokoo_ssi_ids,
	.ops		= &wokoo_ssi_ops,
	.ofdata_to_platdata = wokoo_ssi_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct wokoo_ssi_slave),
	.child_pre_probe = wokoo_ssi_child_pre_probe,
	.probe		= wokoo_ssi_probe,
	.flags		= DM_FLAG_PRE_RELOC,
};
#endif

