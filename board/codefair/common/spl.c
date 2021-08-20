/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <spl.h>

#include <asm/io.h>
#include <asm/gpio.h>
#include <linux/sizes.h>
#include <asm/arch-wokoo/clock.h>
#include <asm/arch-wokoo/wokoo_ddr.h>
#include <asm/arch-wokoo/wokoo_mux.h>
#include <asm/arch-wokoo/wokoo_pwr.h>
#include <asm/arch-wokoo/wokoo_uart.h>

#define MUX_PIN_BASE  ( 0xA0153000UL)

#define MUXPIN_MUX0  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x000))
#define MUXPIN_MUX1  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x004))
#define MUXPIN_MUX2  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x008))
#define MUXPIN_MUX3  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x00c))
#define MUXPIN_MUX4  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x010))
#define MUXPIN_MUX5  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x014))
#define MUXPIN_MUX6  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x018))
#define MUXPIN_MUX7  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x01c))
#define MUXPIN_TST_PIN_CTRL0  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x040))
#define MUXPIN_TST_PIN_CTRL1  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x044))
#define MUXPIN_PULL_EN0  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x070))
#define MUXPIN_PULL_EN1  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x074))
#define MUXPIN_PULL_EN2  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x078))
#define MUXPIN_PULL_EN3  (*(volatile unsigned int *)(MUX_PIN_BASE + 0x07c))

#define GPIO0_BASE    ( 0xA014A000UL)
//#define AP_PWR_BASE   ( 0xA0151000UL)

#define GPIO0_PORT_DR0  (*(volatile unsigned int *)(GPIO0_BASE + 0x000))
#define GPIO0_PORT_DR1  (*(volatile unsigned int *)(GPIO0_BASE + 0x004))
#define GPIO0_PORT_DR2  (*(volatile unsigned int *)(GPIO0_BASE + 0x008))
#define GPIO0_PORT_DR3  (*(volatile unsigned int *)(GPIO0_BASE + 0x00c))
#define GPIO0_PORT_DR4  (*(volatile unsigned int *)(GPIO0_BASE + 0x010))
#define GPIO0_PORT_DR5  (*(volatile unsigned int *)(GPIO0_BASE + 0x014))
#define GPIO0_PORT_DR6  (*(volatile unsigned int *)(GPIO0_BASE + 0x018))
#define GPIO0_PORT_DR7  (*(volatile unsigned int *)(GPIO0_BASE + 0x01c))

#define GPIO0_PORT_DDR0  (*(volatile unsigned int *)(GPIO0_BASE + 0x020))
#define GPIO0_PORT_DDR1  (*(volatile unsigned int *)(GPIO0_BASE + 0x024))
#define GPIO0_PORT_DDR2  (*(volatile unsigned int *)(GPIO0_BASE + 0x028))
#define GPIO0_PORT_DDR3  (*(volatile unsigned int *)(GPIO0_BASE + 0x02c))
#define GPIO0_PORT_DDR4  (*(volatile unsigned int *)(GPIO0_BASE + 0x030))
#define GPIO0_PORT_DDR5  (*(volatile unsigned int *)(GPIO0_BASE + 0x034))
#define GPIO0_PORT_DDR6  (*(volatile unsigned int *)(GPIO0_BASE + 0x038))
#define GPIO0_PORT_DDR7  (*(volatile unsigned int *)(GPIO0_BASE + 0x03c))

#define GPIO0_EXT_PORT0  (*(volatile unsigned int *)(GPIO0_BASE + 0x040))
#define GPIO0_EXT_PORT1  (*(volatile unsigned int *)(GPIO0_BASE + 0x044))
#define GPIO0_EXT_PORT2  (*(volatile unsigned int *)(GPIO0_BASE + 0x048))
#define GPIO0_EXT_PORT3  (*(volatile unsigned int *)(GPIO0_BASE + 0x04c))


/* MUX base address */
static struct wokoo_mux  *base  = (struct wokoo_mux *)WOKOO_MUX_BASE;




/*
 * wokoo_iomux_func - set pin to device pin
 *
 * @base: mux base address
 * @pin: pin
 */
static void wokoo_iomux_func(struct wokoo_mux *base, u32 pin)
{
	WOKOO_MUX_PIN_SET_FUNC(base, pin);
}

/*
 * wokoo_iomux_gpio - set pin to gpio pin
 *
 * @base: mux base address
 * @pin: pin
 */
static void wokoo_iomux_gpio(struct wokoo_mux *base, u32 pin)
{
	WOKOO_MUX_PIN_SET_GPIO(base, pin);
}

/*
 * wokoo_iomux_pull - enable gpio pull
 *
 * @base: mux base address
 * @pin: gpio pin
 * @enable: 1/0
 */
static void wokoo_iomux_pull(struct wokoo_mux *base, u32 gpio, u32 enable)
{
	WOKOO_MUX_PIN_SET_PULL(base, gpio, enable);
}

static void uart_iomux_init(void)
{
	/* mux to uart0 */
	wokoo_iomux_func(base, WOKOO_PIN__GPIO53__UART0_TX);
	wokoo_iomux_func(base, WOKOO_PIN__GPIO54__UART0_RX);
	/* pull up uart0_tx and pull disable uart0_rx */
	wokoo_iomux_pull(base, 53, 1);
	wokoo_iomux_pull(base, 54, 1);

	/* just for gpio test */
	wokoo_iomux_gpio(base, WOKOO_PIN__GPIO99__LCDC_CSM_N);
}

static void ccgr_init(void)
{
}

static void spl_dram_init(void)
{
	#if defined(CONFIG_WOKOO_DDR3)

	ddr3_init();
	#else
	ddr_init();
	#endif
}

#if CONFIG_IS_ENABLED(BOARD_INIT)
void spl_board_init(void)
{
	preloader_console_init();
}
#endif

static void spl_arch_gtimer_init(void)
{
	set_gtm_clk(0, COUNTER_FREQUENCY / 1000);
	enable_gtm_clk(1);
	set_ddr_axi_clk();

	/* Writer counter frequency */
	asm volatile("mcr p15, 0, %0, c14, c0, 0"
			: : "r"(COUNTER_FREQUENCY));
}

void board_init_f(ulong dummy)
{
	ccgr_init();

	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	uart_iomux_init();

	/* UART clocks enabled and gd valid - init serial console */
#if !CONFIG_IS_ENABLED(BOARD_INIT)
	preloader_console_init();
#endif

#ifdef CONFIG_WOKOO_SSI
	/* Set bus_mclk to 1/12 pll */
	set_bus_clk(get_pllout() / 12);
#else
#ifdef CONFIG_WOKOO_QSPI
	/* Set bus_mclk to 1/4 pll */
	set_bus_clk(get_pllout() / 4);
#endif
#endif

	/* setup GP timer */
#if !CONFIG_IS_ENABLED(SYSCOUNTER_TIMER)
	timer_init();
#endif

#if !CONFIG_IS_ENABLED(SYS_ARCH_TIMER)
	spl_arch_gtimer_init();
#endif

	//printf("CPU init completed\n");
	udelay(100);
	spl_dram_init();
}


