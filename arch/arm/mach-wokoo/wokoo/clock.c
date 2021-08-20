/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <div64.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <asm/arch-wokoo/clock.h>
#include <asm/arch-wokoo/wokoo_ctl.h>
#include <asm/arch-wokoo/wokoo_pwr.h>
#include <asm/arch-wokoo/wokoo_rtc.h>




/* PWR base addr */
static struct wokoo_pwr  *base  = (struct wokoo_pwr *)WOKOO_PWR_BASE;

/* CTL base addr */
static struct wokoo_ctl  *ctl_base  = (struct wokoo_ctl *)WOKOO_CTL_BASE;

/* RTC base addr */
static struct wokoo_rtc  *rtc_base  = (struct wokoo_rtc *)WOKOO_RTC_BASE;




#ifdef CONFIG_WOKOO_OCOTP
/*
 * enable_ocotp_clk - enabl clock
 *
 * @enable: enable
 */
void enable_ocotp_clk(unsigned char enable)
{
}
#endif

/*
 * enable_usbotg_clk - enabl clock
 *
 * @enable: enable
 */
void enable_usbotg_clk(unsigned char enable)
{
	uint32_t  regval;

	if (enable) {
		writel(readl(&base->USBCLK_EN) | 0x00000101, &base->USBCLK_EN);
		writel(readl(&base->SYSCLK_EN1) | 0x00010001, &base->SYSCLK_EN1);
		/* Old wokoo cpu valid */
		//writel(readl(&base->USBCLKDIV_CTL) | 0x7, &base->USBCLKDIV_CTL);
	} else {
		regval = (readl(&base->USBCLK_EN) & ~0x1) | 0x00000100;
		writel(regval, &base->USBCLK_EN);
		regval = (readl(&base->SYSCLK_EN1) & ~0x1) | 0x00010000;
		writel(regval, &base->SYSCLK_EN1);
	}
}

/*
 * enable_wathchdog - enabl clock
 *
 * @enable: enable
 */
void enable_wathchdog(unsigned char enable)
{
	if (enable)
		writel(readl(&base->MOD_RSTCTL2) | 0x00002000, &base->MOD_RSTCTL2);
	else
		writel(readl(&base->MOD_RSTCTL2) & ~0x00002000, &base->MOD_RSTCTL2);
}

#ifdef CONFIG_WOKOO_UART
/*
 * enable_uart_clk - enabl clock
 *
 * @enable: enable
 * @num: uartx(0, 1, 2)
 */
void enable_uart_clk(unsigned char enable, unsigned num)
{
	u32 mask;

	/* uart 0, 1, 2 --> bit 4, 5, 6 */
	mask = 1 << (num + 4);

	/* enable uart apb pclock */
	if (enable)
		writel(readl(&base->APBPCLK_EN0) | mask, &base->APBPCLK_EN0);
	else
		writel(readl(&base->APBPCLK_EN0) & ~mask, &base->APBPCLK_EN0);
}
#endif

#ifdef CONFIG_SYS_I2C_WOKOO
/*
 * enable_i2c_clk - enabl clock
 *
 * @enable: enable
 * @i2c_num: i2c_num can be from 0 - 1
 */
int enable_i2c_clk(unsigned char enable, unsigned i2c_num)
{
	u32 mask;

	if ( i2c_num > 1)
		return -EINVAL;

	if (enable) {
		/* enable i2cx apb pclock */
		mask = 1 << (i2c_num + 1);
		writel(readl(&base->APBPCLK_EN0) | mask, &base->APBPCLK_EN0);
		/* enable i2cx apb mclock */
		mask = 1 << (i2c_num + 1);
		writel(readl(&base->APBMCLK_EN) | mask, &base->APBMCLK_EN);
	} else {
		/* enable i2cx apb pclock */
		mask = 1 << (i2c_num + 1);
		writel(readl(&base->APBPCLK_EN0) & ~mask, &base->APBPCLK_EN0);
		/* enable i2cx apb mclock */
		mask = 1 << (i2c_num + 1);
		writel(readl(&base->APBMCLK_EN) & ~mask, &base->APBMCLK_EN);
	}

	return 0;
}
#endif

/* spi_num can be 1 QSPI and 0 SSI0 */
int enable_spi_clk(unsigned char enable, unsigned spi_num)
{
	u32 mask;

	if (spi_num > 1)
		return -EINVAL;

	if (enable) {
		if (spi_num == 1) {
			mask = PWR_APBPCLK_EN0_QSPI_PCLK_EN | PWR_APBPCLK_EN0_BIT_WE_QSPI_PCLK_EN;
		} else if (spi_num == 0) {
			mask = PWR_APBPCLK_EN0_SSI0_PCLK_EN | PWR_APBPCLK_EN0_BIT_WE_SSI0_PCLK_EN;
		}
	} else {
		if (spi_num == 1) {
			mask = PWR_APBPCLK_EN0_BIT_WE_QSPI_PCLK_EN;
		} else if (spi_num == 0) {
			mask = PWR_APBPCLK_EN0_BIT_WE_SSI0_PCLK_EN;
		}
	}

	writel(readl(&base->APBPCLK_EN0) | mask, &base->APBPCLK_EN0);
	return 0;
}

/*
 * enable_gtm_clk - enable generic timer clock
 *
 */
int enable_gtm_clk(unsigned char enable)
{
	u32 val;

	val  = readl(&base->A7_GTM_CTL);
	if (enable) {
		/* Enable clock */
		val |= (0x1 << 0) | (1 << 16);
		/* Start generic timer */
		val |= (0x1 << 2) | (1 << 18);
	} else {
		/* Disable clock */
		val &= ~((0x1 << 0) | (1 << 16));
		/* Stop generic timer */
		val &= ~((0x1 << 2) | (1 << 18));
	}

	writel(val, &base->A7_GTM_CTL);
	return 0;
}

/*
 * get_pll_mclk - get clock KHZ
 *
 */
static u32 get_pll_mclk(void)
{
	return get_pllout() / 4;
}

/*
 * set_gtm_clk - set clock KHZ
 *
 */
int set_gtm_clk(u32 parent, u32 clk)
{
	u32 val, mclk;

	val  = readl(&base->A7_GTM_CTL);
	val &= ~(0xff << 8);
	if (parent) {
		/* Select parent clock to pll_mclk */
		val |= (0x1 << 1) | (1 << 17);
		mclk = get_pll_mclk();
		mclk = mclk / clk;
		val |= ((mclk - 1) << 8) | (1 << 20);
	} else {
		/* Select parent clock to pll_mclk */
		val &= ~(0x1 << 1);
		val |= (1 << 17);
		mclk = 16000;
		mclk = mclk / clk;
		val |= ((mclk - 1) << 8) | (1 << 20);
	}

	writel(val, &base->A7_GTM_CTL);
	return 0;
}




/*
 * get_pllout - get freq KHZ
 *
 */
u32 get_pllout(void)
{
	uint32_t val;

	val = (readl(&base->PLLCTL0) & 0xFFF00) >> 8;
	return 160000 * val / 0x14;
}


void set_ddr_axi_clk(void)
{
		int reg = 0;
		reg = readl(&base->DDRAXICLK_CTL);	
		//reg &= ~(0x3 <<8) & ~(0xf) & ~(0xf < 4);		
		//reg  |= (1 << 18) | (1 << 16) |((1 << 17)) | 0x0 <<8  | 0x8 | 0x8 << 4;
		writel(0x73088,&base->DDRAXICLK_CTL);



}


const u32 bus_div_preq_tb[4][4] = {
	/* dr = 0x03 */
	{3, 6,  12, 24},
	/* dr = 0x04 */
	{4, 8,  16, 32},
	/* dr = 0x05 */
	{5, 10, 20, 40},
	/* dr = 0x06 */
	{6, 12, 24, 48},
};

/*
 * set_bus_clk - set clock KHZ
 *
 */
void set_bus_clk(u32 khz)
{
	u32 clk_dr, clk_gr, reg;
	u32 i = 0, j = 0;
	u32 div;

	clk_dr = 0;
	clk_gr = 0;
	div    = get_pllout() / khz;
	if (div < 3) {
		clk_dr = 0x0;
		clk_gr = 0x8;
	} else if (div > 48) {
		clk_dr = 0x3;
		clk_gr = 0x8;
	} else {
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				if (div >= bus_div_preq_tb[i][j] && div <= bus_div_preq_tb[i + 1][j]) {
					if (div == bus_div_preq_tb[i + 1][j]) {
						clk_dr = i + 1;
					} else {
						clk_dr = i;
					}
					clk_gr = 8 / (1 << j);
					//printf("set_bus_clk clock = %d, i = %d, j = %d\n", khz, clk_dr, clk_gr);
					break;
				}
			}
		}
	}

	//printf("set_bus_clk clock = %d, div = %d\n", khz, bus_div_preq_tb[i][j]);
	reg  = clk_gr | (1 << 16);
	reg |= (clk_dr << 4) | (1 << 17);
	writel(reg, &base->SYSCLK_CTL);
}

/*
 * get_mcu_main_clk - get A7 clock freq KHZ
 *
 */
static u32 get_mcu_main_clk(void)
{
	u32 reg, freq;

	reg  = readl(&base->A7_CLK_CTL);
	reg  = reg & 0x1F;
	freq = reg * get_pllout() / 16;

	return freq;
}

/*
 * reset_ssi - reset ssi modules
 *
 */
void reset_ssi(void)
{
	u32 regv;

	/* Disable ssi0 pclk */
	writel(0x0 | PWR_APBPCLK_EN0_BIT_WE_SSI0_PCLK_EN, &base->APBPCLK_EN0);
	writel(0x0 | PWR_SSICLKGR_CTL_SSI0_CLK_GR_WE, &base->SSICLKGR_CTL);
	regv = readl(&base->MOD_RSTCTL3);
	writel(regv | PWR_MOD_RSTCTL3_SSI0_RSTCTL, &base->MOD_RSTCTL3);
	writel(regv, &base->MOD_RSTCTL3);
	/* Enable ssi0 pclk */
	writel(PWR_APBPCLK_EN0_SSI0_PCLK_EN | PWR_APBPCLK_EN0_BIT_WE_SSI0_PCLK_EN, &base->APBPCLK_EN0);
	writel(PWR_SSICLKGR_CTL_SSI0_CLK_GR_WE | (8 << PWR_SSICLKGR_CTL_SSI0_CLK_GR_POS), &base->SSICLKGR_CTL);
}

/*
 * reset_rtc - reset rtc modules
 *
 */
void reset_rtc(void)
{
	u32 regv;

	/* Enable rtc pclk */
	writel(PWR_APBPCLK_EN0_RTC_PCLK_EN | PWR_APBPCLK_EN0_BIT_WE_RTC_PCLK_EN, &base->APBPCLK_EN0);

	/* Enable PMU */
	writel(0x3, &rtc_base->PWEN_CTL);
	/* Disable rtc pclk */
	writel(0x0 | PWR_APBPCLK_EN0_RTC_PCLK_EN, &base->APBPCLK_EN0);
	regv = readl(&base->MOD_RSTCTL2);
	writel(regv | PWR_MOD_RSTCTL2_RTC_RSTCTL, &base->MOD_RSTCTL2);
	udelay(1);
	writel(regv, &base->MOD_RSTCTL2);
	/* Enable rtc pclk */
	writel(PWR_APBPCLK_EN0_RTC_PCLK_EN | PWR_APBPCLK_EN0_BIT_WE_RTC_PCLK_EN, &base->APBPCLK_EN0);
}

/*
 * set_ssi_protocol_mode - set ssi protocol mode
 *
 */
void set_ssi_protocol_mode(u32 mode)
{
	writel(mode, &ctl_base->SSI0_PROTOCOL_CTRL);
}

/*
 * set_apb_pclk - set clock KHZ
 *
 */
void set_apb_pclk(u32 khz)
{
	u32 reg;
	u32 div;

	div    = get_bus_clk() / khz;

	if (div < 1 || div > 8) {
		return;
	}

	div = 8 / div;

	reg  = (div - 1) | (1 << 16);
	reg |= (div - 1) << 0x4 | (1 << 17);
	writel(reg, &base->CTLPCLK_CTL);
}

/*
 * set_ssi_clk - set clock KHZ
 *
 */
void set_ssi_clk(u32 khz)
{
	u32 clk_dr, clk_gr, reg;
	u32 i = 0, j = 0;
	u32 div, tmp;

	clk_dr = 0;
	clk_gr = 0;
	div    = get_pll_mclk() / khz;

	if (div < 1 || div > 128) {
		return;
	}

	for (i = 0; i < 3; i++) {
		tmp = div / (1 << i);
		for (j = 1; j < 16; j++) {
			if (j >= tmp && j < tmp + 1) {
				//printf("set_ssi_clk clock = %d, div = %d * %d\n", khz, 1 << i, j);
				clk_gr = 8 / (1 << i);
				clk_dr = j - 1;
				reg  = clk_gr | (1 << 16);
				reg |= (clk_gr << 4) | (1 << 17);
				writel(reg, &base->SSICLKGR_CTL);
				reg  = clk_dr | (1 << 16);
				reg |= (clk_dr << 4) | (1 << 17);
				writel(reg, &base->SSICLKDIV_CTL);
				return;
			}
		}
	}
}

/*
 * get_bus_clk - get clock KHZ
 *
 */
u32 get_bus_clk(void)
{
	u32 clk_dr, clk_gr, reg, freq;

	reg    = readl(&base->SYSCLK_CTL);
	clk_dr = ((reg & 0x30) >> 4) + 3;
	clk_gr = reg & 0x0F;
	freq   = (clk_gr * get_pllout() / 8)/ clk_dr;

	return freq;
}

/*
 * get_apb_clk - get clock KHZ
 *
 */
static u32 get_apb_clk(void)
{
	u32 reg, freq;

	reg  = readl(&base->SYSCLK_CTL);
	reg  = reg & 0x7;
	freq = get_bus_clk() * (reg + 1) / 8;

	return freq;
}

/*
 * get_uart_clk - get clock HZ
 *
 */
unsigned long get_uart_clk(unsigned num)
{
	unsigned long uart_mclk;
	u32 reg;
	u32 div = 0, mul = 0;

	if (num > 3)
		return 0;

	reg  = readl(&base->UARTCLKGR_CTL);

	switch (num) {
	case 0:
		reg = reg & 0x0f;
		break;
	case 1:
		reg = (reg & 0xf0) >> 4;
		break;
	case 2:
		reg = (reg & 0xf00) >> 8;
		break;
	}

	uart_mclk = get_pll_mclk() * reg / 8;

	switch (num) {
	case 0:
		reg  = readl(&base->UART0CLK_CTL);
		div  = reg & 0xffff;
		mul  = (reg & 0xffff0000) >> 16;
		break;
	case 1:
		reg  = readl(&base->UART1CLK_CTL);
		div  = reg & 0xffff;
		mul  = (reg & 0xffff0000) >> 16;
		break;
	case 2:
		reg  = readl(&base->UART2CLK_CTL);
		div  = reg & 0xffff;
		mul  = (reg & 0xffff0000) >> 16;
		break;
	}

	return (uart_mclk * 1000 / div)  * mul / 2;
}

/*
 * get_i2c_clk - get clock KHZ
 *
 */
static u32 get_i2c_clk(unsigned num)
{
	u32 reg;

	if (num > 2)
		return 0;

	if (num == 0)
		reg = readl(&base->I2CCLK_CTL) & 0x1f;
	else
		reg = (readl(&base->I2CCLK_CTL) & 0x1f00) >> 0;

	return get_pll_mclk() / (1 + reg);
}

/*
 * get_spi_clk - get clock KHZ
 *
 */
static u32 get_spi_clk(unsigned num)
{
	u32 gr, div;

	if (num > 1)
		return 0;

	if (num == 0) {
		gr  = readl(&base->SSICLKGR_CTL) & 0x0f;
		div = readl(&base->SSICLKDIV_CTL) & 0x0f;
	} else {
		gr  = ((readl(&base->SSICLKGR_CTL) & 0xf0) >> 4) + 1;
		div = ((readl(&base->SSICLKDIV_CTL) & 0xf0) >> 4) + 1;
	}

	return get_pll_mclk() * gr / div;
}

/*
 * get_usbotg_clk - get clock KHZ
 *
 */
static u32 get_usbotg_clk(void)
{
	u32 reg, base_freq;
	u32 freq = 0;

	reg       = readl(&base->USBCLKDIV_CTL);
	base_freq = (reg & 0xe00) >> 9;

	switch (base_freq) {
	case 0:
		freq = 9600;
		break;
	case 1:
		freq = 10000;
		break;
	case 2:
		freq = 12000;
		break;
	case 3:
		freq = 19200;
		break;
	case 4:
		freq = 20000;
		break;
	case 5:
		freq = 24000;
		break;
	}

	return freq;
}

/*
 * get_axi_clk - get clock KHZ
 *
 */
static u32 get_axi_clk(void)
{
	u32 clk_dr, clk_gr, reg, freq;

	reg    = readl(&base->A7AXI_MAINCLK_CTL);
	clk_dr = (reg & 0x30 >> 4) + 3;
	clk_gr = reg & 0x0F;
	freq   = (clk_gr * get_pllout() / 8) / clk_dr;

	return freq;
}

/*
 * get_ddr_clk - get clock KHZ
 *
 */
static u32 get_ddr_clk(void)
{
	u32 clk_dr, clk_gr, reg, freq;

	reg    = readl(&base->DDRAXICLK_CTL);
	clk_dr = (reg & 0x300 >> 8) + 3;
	clk_gr = reg & 0x0F;
	freq   = (clk_gr * get_pllout() / 8) / clk_dr;

	return freq;
}

#ifdef CONFIG_FSL_QSPI
void enable_qspi_clk(int qspi_num)
{
	enable_spi_clk(1, 1);
}
#endif

/*
 * wokoo_get_clock
 */
unsigned int wokoo_get_clock(enum wokoo_clock clk)
{
	switch (clk) {
	case WOKOO_ARM_CLK:
		return get_mcu_main_clk();
	case WOKOO_BUS_CLK:
		return get_bus_clk();
	case WOKOO_APB_CLK:
		return get_apb_clk();
	case WOKOO_I2C_CLK:
		return get_i2c_clk(0);
	case WOKOO_UART_CLK:
		return get_uart_clk(0) / 1000;
	case WOKOO_CSPI_CLK:
		return get_spi_clk(1);
	case WOKOO_AXI_CLK:
		return get_axi_clk();
	case WOKOO_DDR_CLK:
		return get_ddr_clk();
	case WOKOO_USB_CLK:
		return get_usbotg_clk();
	default:
		printf("Unsupported WOKOO CLK: %d\n", clk);
		break;
	}

	return 0;
}

#ifndef CONFIG_SPL_BUILD
/*
 * Dump some core clockes.
 */
int do_wokoo_showclocks(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 freq;
	freq = wokoo_get_clock(WOKOO_APB_CLK);
	printf("PLL_APB    %8d kHz\n", freq);
	freq = wokoo_get_clock(WOKOO_BUS_CLK);
	printf("PLL_BUS    %8d kHz\n", freq);
	freq = wokoo_get_clock(WOKOO_USB_CLK);
	printf("PLL_OTG    %8d kHz\n", freq);

	printf("\n");
	printf("ARM        %8d kHz\n", wokoo_get_clock(WOKOO_ARM_CLK));
	printf("UART       %8d kHz\n", wokoo_get_clock(WOKOO_UART_CLK));
#ifdef CONFIG_MXC_SPI
	printf("CSPI       %8d kHz\n", wokoo_get_clock(WOKOO_CSPI_CLK));
#endif
	printf("AXI        %8d kHz\n", wokoo_get_clock(WOKOO_AXI_CLK));
	printf("DDR        %8d kHz\n", wokoo_get_clock(WOKOO_DDR_CLK));

	return 0;
}

/***************************************************/

U_BOOT_CMD(
	clocks,	CONFIG_SYS_MAXARGS, 1, do_wokoo_showclocks,
	"display clocks",
	""
);
#endif
