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
#include <asm/arch/wokoo_usbotg.h>
#include <asm/arch-wokoo/clock.h>
#include <asm/io.h>




/* DDR base addr */
//static struct wokoo_usbotg  *wokoo_usbotg = (struct wokoo_usbotg *)WOKOO_USBOTG_BASE;
static struct wokoo_ctrl    *wokoo_ctrl   = (struct wokoo_ctrl *)WOKOO_CTRL_BASE;



void wokoo_otg_phy_init(void)
{
	uint32_t tmp, i;

	writel(0x00000000, &wokoo_ctrl->PHY_RST_CTRL);

	tmp = readl(&wokoo_ctrl->PHY_SUSPEND);
	tmp |= 0x00000002;
	tmp &= 0xFFFFFFFE;
	writel(tmp, &wokoo_ctrl->PHY_SUSPEND);
	for (i = 0; i < 0x1000; i++);

	writel(0x00000001, &wokoo_ctrl->PHY_RST_CTRL);

	enable_usbotg_clk(1);

	for (i = 0; i < 0x1000; i++);

	tmp = readl(&wokoo_ctrl->PHY_SUSPEND);
	tmp |= 0x00000001;
	writel(tmp, &wokoo_ctrl->PHY_SUSPEND);
	for (i = 0; i < 0x1000; i++);

	for (i = 0; i < 0x1000; i++);
	tmp = readl(&wokoo_ctrl->PHY_RST_CTRL);
	tmp |= 0x00000010;
	writel(tmp, &wokoo_ctrl->PHY_RST_CTRL);
}

