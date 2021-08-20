/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <dm.h>
#include <asm/io.h>
#include <wdt.h>
#include <watchdog.h>
#include <asm/arch-wokoo/clock.h>
#include <asm/arch-wokoo/wokoo_wdt.h>
#include <asm/arch-wokoo/wokoo_pwr.h>




/* WDT base addr */
static struct wokoo_wdt *base = (struct wokoo_wdt *)WOKOO_WDT_BASE;
static struct wokoo_pwr *pwr  = (struct wokoo_pwr *)WOKOO_PWR_BASE;



/*
 *  wathdog_close - close wathdog
 *
 */
static void wathdog_close(void)
{
	enable_wathchdog(0);
}

/*
 *  wathdog_open - open wathdog
 *
 */
static void wathdog_open(void)
{
	enable_wathchdog(1);
}

/*
 *  wathdog_restart - restart wathdog
 *
 */
static void wathdog_restart(void)
{
	writel(0x76, &base->CRR);
	writel(readl(&base->CR) | 0x01, &base->CR);
}

/*
 *  wathdog_set_top_bit - set top bit
 *
 */
static void wathdog_set_top_bit(int top)
{
	writel((readl(&base->TORR) & 0xFFFFFFF0) + (top & 0x0000000F), &base->TORR);
}

/*
 *  wathdog_set_mode - set mode
 *
 */
static void wathdog_set_mode(int mode)
{
	if (mode == 0)
		writel(readl(&base->CR) & 0xFFFFFFFD, &base->CR);
	else
		writel(readl(&base->CR) | 0x00000002, &base->CR);
}

/*
 *  wathdog_start - start wathdog
 *
 */
void wathdog_start(void)
{
	writel(readl(&base->CR) | 0x01, &base->CR);
}

/*
 *  wathdog_config - config wathdog
 *
 */
static void wathdog_config(int mode, int top)
{
	wathdog_close();
	wathdog_open();
	wathdog_set_top_bit(top);
	wathdog_set_mode(mode);
	wathdog_start();
}

static void wokoo_watchdog_expire_now(void)
{
	wathdog_config(1, 0x2);
	/* Watchdog can not full chip reset */
	wathdog_restart();
	/* Full chip reset */
	writel(0xFF, &pwr->SFRST_CTL);
	while (1) {
		/*
		 * spin before reset
		 */
	}
}

#if !defined(CONFIG_WOKOO_WATCHDOG) || \
	(defined(CONFIG_WOKOO_WATCHDOG) && !CONFIG_IS_ENABLED(WDT))
void __attribute__((weak)) reset_cpu(ulong addr)
{
	wokoo_watchdog_expire_now();
}
#endif

#if defined(CONFIG_WOKOO_WATCHDOG)
static void wokoo_watchdog_reset(void)
{
#ifndef CONFIG_WATCHDOG_RESET_DISABLE
	wathdog_config(1, 0x08);
	wathdog_restart();
#endif /* CONFIG_WATCHDOG_RESET_DISABLE*/
}

static void wokoo_watchdog_init(void)
{
	wathdog_config(1, 0xc);
}

#if !CONFIG_IS_ENABLED(WDT)
void hw_watchdog_reset(void)
{
	wokoo_watchdog_reset();
}

void hw_watchdog_init(void)
{
	wokoo_watchdog_init();
}
#else
struct wokoo_wdt_priv {
	void __iomem *base;
};

static int wokoo_wdt_reset(struct udevice *dev)
{
	wokoo_watchdog_reset();

	return 0;
}

static int wokoo_wdt_expire_now(struct udevice *dev, ulong flags)
{
	wokoo_watchdog_expire_now();
	hang();

	return 0;
}

static int wokoo_wdt_start(struct udevice *dev, u64 timeout, ulong flags)
{
	wokoo_watchdog_init();

	return 0;
}

static int wokoo_wdt_probe(struct udevice *dev)
{
	struct wokoo_wdt_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -ENOENT;

	return 0;
}

static const struct wdt_ops wokoo_wdt_ops = {
	.start		= wokoo_wdt_start,
	.reset		= wokoo_wdt_reset,
	.expire_now	= wokoo_wdt_expire_now,
};

static const struct udevice_id wokoo_wdt_ids[] = {
	{ .compatible = "wokoo,wokoo-wdt" },
	{}
};

U_BOOT_DRIVER(wokoo_wdt) = {
	.name		= "wokoo_wdt",
	.id		= UCLASS_WDT,
	.of_match	= wokoo_wdt_ids,
	.probe		= wokoo_wdt_probe,
	.ops		= &wokoo_wdt_ops,
	.priv_auto_alloc_size = sizeof(struct wokoo_wdt_priv),
	.flags		= DM_FLAG_PRE_RELOC,
};
#endif
#endif
