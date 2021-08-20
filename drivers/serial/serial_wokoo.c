/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <watchdog.h>
#include <asm/arch-wokoo/wokoo_uart.h>
#include <asm/arch-wokoo/clock.h>
#include <serial.h>
#include <linux/compiler.h>




DECLARE_GLOBAL_DATA_PTR;




/*
 *  _wokoo_serial_init - uart init
 *
 * @base: base address
 */
static void _wokoo_serial_init(struct wokoo_uart *base)
{
	/* enable fifo */
	writel(UART_FCR_FIFOE | UART_FCR_XFIFOR | UART_FCR_RFIFOR, &base->FCR);
	/* set frame */
	writel(readl(&base->TCR) | 0x03, &base->TCR);
	/* enable programable THRE, intr */
	writel(0x83, &base->IER);
	/* set data bit, stop bit, parity bit */
	writel(UART_TCR_DLS_8BITS | UART_TCR_STOPBITS_1 | UART_PARITY_NONE, &base->TCR);
}


/*
 *  _wokoo_serial_set_baud - set uart baudrate
 *
 * @base: base address
 * @baudrate: baudrate
 */
static int _wokoo_serial_set_baud(struct wokoo_uart *base, unsigned long baudrate)
{
	uint16_t dl;
	unsigned long uart_mclk;

	uart_mclk = get_uart_clk(0) / 16;
	dl        = uart_mclk / baudrate;

	/* DLAB enable */
	writel(readl(&base->TCR) | UART_TCR_DLAB, &base->TCR);
	writel(dl & 0xFF, &base->DLL);
	writel((dl >> 8) & 0xFF, &base->DLH);
	/* DLAB disable */
	writel(readl(&base->TCR) & ~UART_TCR_DLAB, &base->TCR);
	return 0;
}

static void _wokoo_serial_setbrg(struct wokoo_uart *base, unsigned long baudrate)
{
	_wokoo_serial_set_baud(base, baudrate);
}

#if !CONFIG_IS_ENABLED(DM_SERIAL)

#ifndef WOKOO_UART_BASE
#error "define WOKOO_UART_BASE to use the WOKOO UART driver"
#endif

/* UART base address */
#define wokoo_base	((struct wokoo_uart *)WOKOO_UART_BASE)

static void wokoo_uart_put_char(char val)
{
	/* write to the reg */
	while ((readl(&wokoo_base->TSR) & UART_TSR_THRE) != UART_TSR_THRE);
	writel(val, &wokoo_base->THR);
}

static int wokoo_serial_getc(void)
{
	int c = 0;

	while ((readl(&wokoo_base->TSR) & UART_TSR_DR) != UART_TSR_DR);
	c = readl(&wokoo_base->RBR) & 0xFF;

	return c;
}

static void wokoo_serial_putc(const char c)
{
	/* If \n, also do \r */
	if (c == '\n')
		serial_putc('\r');

	wokoo_uart_put_char(c);
}

/* Test whether a character is in the RX buffer */
static int wokoo_serial_tstc(void)
{
	/* If receive fifo is empty, return false */
	if ((readl(&wokoo_base->TSR) & UART_TSR_DR) != UART_TSR_DR)
		return 0;
	
	return 1;
}

static void wokoo_serial_setbrg(void)
{
	if (!gd->baudrate)
		gd->baudrate = CONFIG_BAUDRATE;

	_wokoo_serial_setbrg(wokoo_base, gd->baudrate);
}

/*
 * Initialise the serial port with the given baudrate. The settings
 * are always 8 data bits, no parity, 1 stop bit, no start bits.
 */
static int wokoo_serial_init(void)
{
	_wokoo_serial_init(wokoo_base);

	serial_setbrg();

	return 0;
}

static struct serial_device wokoo_serial_drv = {
	.name	= "wokoo_serial",
	.start	= wokoo_serial_init,
	.stop	= NULL,
	.setbrg	= wokoo_serial_setbrg,
	.putc	= wokoo_serial_putc,
	.puts	= default_serial_puts,
	.getc	= wokoo_serial_getc,
	.tstc	= wokoo_serial_tstc,
};

void wokoo_serial_initialize(void)
{
	serial_register(&wokoo_serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &wokoo_serial_drv;
}
#endif

#if CONFIG_IS_ENABLED(DM_SERIAL)

int wokoo_serial_setbrg(struct udevice *dev, int baudrate)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	struct wokoo_uart *uart = plat->reg;

	_wokoo_serial_setbrg(uart, baudrate);

	return 0;
}

static int wokoo_serial_probe(struct udevice *dev)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	struct wokoo_uart *uart = plat->reg;

	_wokoo_serial_init(uart);

	return 0;
}

static int wokoo_serial_getc(struct udevice *dev)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	struct wokoo_uart *const uart = plat->reg;

	while ((readl(&uart->TSR) & UART_TSR_DR) != UART_TSR_DR);
	return readl(&uart->RBR) & 0xFF;
}

static int wokoo_serial_putc(struct udevice *dev, const char ch)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	struct wokoo_uart *const uart = plat->reg;

	while ((readl(&uart->TSR) & UART_TSR_THRE) != UART_TSR_THRE);
	writel(ch, &uart->THR);

	return 0;
}

static int wokoo_serial_pending(struct udevice *dev, bool input)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	struct wokoo_uart *const uart = plat->reg;

	if (input)
		return ((readl(&uart->TSR) & UART_TSR_DR) == UART_TSR_DR) ? 1 : 0;
	else
		return ((readl(&uart->TSR) & UART_TSR_THRE) == UART_TSR_THRE) ? 1 : 0;
}

static const struct dm_serial_ops wokoo_serial_ops = {
	.putc = wokoo_serial_putc,
	.pending = wokoo_serial_pending,
	.getc = wokoo_serial_getc,
	.setbrg = wokoo_serial_setbrg,
};

#if CONFIG_IS_ENABLED(OF_CONTROL)
static int wokoo_serial_ofdata_to_platdata(struct udevice *dev)
{
	struct wokoo_serial_platdata *plat = dev->platdata;
	fdt_addr_t addr;

	addr = devfdt_get_addr(dev);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	plat->reg = (struct wokoo_uart *)addr;
	return 0;
}

static const struct udevice_id wokoo_serial_ids[] = {
	{ .compatible = "wokoo,wokoo-uart" },
	{ }
};
#endif

U_BOOT_DRIVER(serial_wokoo) = {
	.name	= "serial_wokoo",
	.id	= UCLASS_SERIAL,
#if CONFIG_IS_ENABLED(OF_CONTROL)
	.of_match = wokoo_serial_ids,
	.ofdata_to_platdata = wokoo_serial_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct wokoo_serial_platdata),
#endif
	.probe	= wokoo_serial_probe,
	.ops	= &wokoo_serial_ops,
	.flags = DM_FLAG_PRE_RELOC,
};
#endif

#ifdef CONFIG_DEBUG_UART_WOKOO
#include <debug_uart.h>

static void debug_wokoo_uart_put_char(char val)
{
	struct wokoo_uart *base = (struct wokoo_uart *)WOKOO_UART_BASE;

	/* write to the reg */
	while ((readl(&base->TSR) & UART_TSR_THRE) != UART_TSR_THRE);
	writel(val, &base->THR);
}

static inline void _debug_uart_init(void)
{
	struct wokoo_uart *base = (struct wokoo_uart *)WOKOO_UART_BASE;

	_wokoo_serial_init(base);
	_wokoo_serial_setbrg(base, CONFIG_BAUDRATE);
}

static inline void _debug_uart_putc(int ch)
{
	debug_wokoo_uart_put_char(ch);
}

DEBUG_UART_FUNCS

#endif
