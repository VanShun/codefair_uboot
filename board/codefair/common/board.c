/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <env.h>
#include <mmc.h>
#include <usb.h>
#include <watchdog.h>
#include <asm/gpio.h>
#include <usb/dwc2_udc.h>
#include <asm/mach-types.h>
#include <asm/arch-wokoo/wokoo_usbotg.h>

#include "board.h"
extern u32 wokoo_ddr_size(void);

DECLARE_GLOBAL_DATA_PTR;

int board_late_init(void)
{
	u32 vgpio0, vgpio1, vgpio2, mode;

	env_set("modeboot", "spiboot");
	env_set("console", "ttyWK0");

	gpio_direction_input(0);
	gpio_direction_input(1);
	gpio_direction_input(2);

	vgpio0 = gpio_get_value(0);
	vgpio1 = gpio_get_value(1);
	vgpio2 = gpio_get_value(2);

	mode   = ((vgpio2 & 0x1) << 2) + ((vgpio1 & 0x1) << 1) + (vgpio0 & 0x1);
	if (mode == 3) {
		/* SPI boot */
#ifdef CONFIG_DM_SPI
		env_set("spidev", "1:0");
		env_set("fastboot_spidev", "1:0");
#else
		env_set("spidev", "1:0");
		env_set("fastboot_spidev", "1:0");
#endif
	} else{
		/* SPI boot */
		env_set("spidev", "0:0");
		env_set("fastboot_spidev", "0:0");
	}

#ifdef CONFIG_HW_WATCHDOG
	hw_watchdog_init();
#endif

	return 0;
}

#ifdef CONFIG_USB_GADGET
static struct dwc2_plat_otg_data otg_data = {
	.rx_fifo_sz	= 512,
	.np_tx_fifo_sz	= 16,
	.tx_fifo_sz	= 128,
};
#endif

int board_init(void)
{
	/* Address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;
	gd->bd->bi_arch_number = MACH_TYPE_WOKOO;

	/* USB OTG PHY init */
	wokoo_otg_phy_init();

#ifdef CONFIG_USB_GADGET
	otg_data.regs_otg = CONFIG_USB_DWC2_REG_ADDR;

	/* Enable USB UDC */
	return dwc2_udc_probe(&otg_data);
#else
	return 0;
#endif
}

int dram_init(void)
{
	gd->ram_size = wokoo_ddr_size();

	return 0;
}

