/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_USBOTG_H_
#define _WOKOO_USBOTG_H_



#define WOKOO_USBOTG_BASE			0xA0300000
#define WOKOO_CTRL_BASE				0xA0060000

struct wokoo_usbotg
{
	uint32_t	base;
};

struct wokoo_ctrl
{
	uint32_t	reserved[84];
	uint32_t	PHY_RST_CTRL;
	uint32_t	PHY_SUSPEND;
};


void wokoo_otg_phy_init(void);

#endif /* _WOKOO_USBOTG_H_ */
