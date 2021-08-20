/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <linux/types.h>
#include <asm/io.h>
#include <asm/types.h>
#include <wait_bit.h>
#include <asm/arch-wokoo/clock.h>
#include <asm/arch-wokoo/wokoo_pwr.h>
#include <asm/arch-wokoo/wokoo_uart.h>




#if CONFIG_SPL_BUILD
/* PWR base addr */
static struct wokoo_pwr  *base  = (struct wokoo_pwr *)WOKOO_PWR_BASE;
#endif

u32 get_nr_cpus(void)
{
	return 1;
}

u32 get_cpu_rev(void)
{
	return 1;
}

u32 get_cpu_speed_grade_hz(void)
{
	return get_pllout();
}

#if CONFIG_SPL_BUILD
/*
 *  wokoo_pll_freq_without_slp - set pll out freq without sleep
 *
 *  @freq: freq
 */
static void wokoo_pll_freq_without_slp(uint32_t freq)
{
	if (freq % 16 == 0) {
		int f16x = freq / 16;

		/* freq > 56M && freq < 800M */
		if (f16x > 4 && f16x <= 50)
			writel((readl(&base->PLLCTL0) & ~PWR_PLLCTL0_FBDIV_MSK) + ((f16x * 2) << PWR_PLLCTL0_FBDIV_POS), &base->PLLCTL0);
		else
			writel((readl(&base->PLLCTL0) & ~PWR_PLLCTL0_FBDIV_MSK) + (20 << PWR_PLLCTL0_FBDIV_POS), &base->PLLCTL0);
	} else {
		/* default 160M */
		writel((readl(&base->PLLCTL0) & ~PWR_PLLCTL0_FBDIV_MSK) + (20 << PWR_PLLCTL0_FBDIV_POS), &base->PLLCTL0);
	}

	writel(PWR_PLL_FREQ_CTL_BIT_WE_CHG_MK | 0, &base->PLL_FREQ_CTL);
	writel(PWR_PLL_FREQ_CTL_BIT_WE_CHG_START | PWR_PLL_FREQ_CTL_CHG_START, &base->PLL_FREQ_CTL);

	/* set a7 clock = (16 / 16) * pll_out */
	writel(PWR_A7_CLK_CTL_BIT_WE_CLK_GR + 16, &base->A7_CLK_CTL);
}

/*
 *  wokoo_uart_baudrate_standard - set uart to standard baudrate
 *
 */
static void wokoo_uart_baudrate_standard(void)
{

	int pll_out_freq, pll16x;
	uint16_t mul, div;

	/* get_pllout() = XKHZ */
	pll_out_freq = get_pllout() / 1000;
	pll16x = pll_out_freq / 16;
	if (pll16x > 10) {
		mul = (uint16_t)(UART_20XOSC_MUL);
		div = (uint16_t)(UART_20XOSC_DIV * pll16x);
	} else {
		mul = (uint16_t)(UART_20XOSC_MUL_LOW_FREQ);
		div = (uint16_t)(UART_20XOSC_DIV * pll16x);

	}

	/* Set uart mclk = 14745600HZ, set GR = 8, uart_mclk = pll_mclk * gr / 8 */
	writel(PWR_UARTCLKGR_CTL_UART0_CLK_GR_WE + 0x00, &base->UARTCLKGR_CTL);
	/* pll_mclk = pll_out / 4, uart_mclk = pll_mclk * mul / div / 2 */
	writel(((uint32_t)mul << PWR_UARTXCLK_CTL_MUL_POS) + (uint32_t)div, &base->UART0CLK_CTL);
	writel(PWR_UARTCLKGR_CTL_UART0_CLK_GR_WE + (0x8 << PWR_UARTCLKGR_CTL_UART0_CLK_GR_POS), &base->UARTCLKGR_CTL);

	writel(PWR_UARTCLKGR_CTL_UART1_CLK_GR_WE + 0x00, &base->UARTCLKGR_CTL);
	writel(((uint32_t)mul << PWR_UARTXCLK_CTL_MUL_POS) + (uint32_t)div, &base->UART1CLK_CTL);
	writel(PWR_UARTCLKGR_CTL_UART1_CLK_GR_WE + (0x8 << PWR_UARTCLKGR_CTL_UART1_CLK_GR_POS), &base->UARTCLKGR_CTL);

	writel(PWR_UARTCLKGR_CTL_UART2_CLK_GR_WE + 0x00, &base->UARTCLKGR_CTL);
	writel(((uint32_t)mul << PWR_UARTXCLK_CTL_MUL_POS) + (uint32_t)div, &base->UART2CLK_CTL);
	writel(PWR_UARTCLKGR_CTL_UART2_CLK_GR_WE + (0x8 << PWR_UARTCLKGR_CTL_UART2_CLK_GR_POS), &base->UARTCLKGR_CTL);
}

/*
 *  wokoo_set_a7axi_mainclk - set A7 AXI main clock
 *
 */
static void wokoo_set_a7axi_mainclk(void)
{
	writel(PWR_A7AXI_MAINCLK_CTL_BIT_WE_CLK_GR | 0x8, &base->A7AXI_MAINCLK_CTL);
	writel(PWR_A7AXI_MAINCLK_CTL_BIT_WE_CLK_DR | (0x0 << 4), &base->A7AXI_MAINCLK_CTL);
}
#endif

u32 get_cpu_temp_grade(int *minc, int *maxc)
{
	if (minc && maxc) {
		*minc = -20;
		*maxc = 60;
	}
	return 0;
}

#ifdef CONFIG_REVISION_TAG
u32 __weak get_board_rev(void)
{
	return 1;
}
#endif

int arch_cpu_init(void)
{
#if CONFIG_SPL_BUILD
	wokoo_pll_freq_without_slp(768);
	wokoo_uart_baudrate_standard();
	wokoo_set_a7axi_mainclk();
#endif
	return 0;
}

int board_postclk_init(void)
{
	return 0;
}

void reset_misc(void)
{
}

void s_init(void)
{
}

void gpr_init(void)
{
}


