/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/spl.h>
#include <asm/gpio.h>
#include <spl.h>
#include <g_dnl.h>

#include <usb/dwc2_udc.h>
#include <asm/mach-types.h>
#include <asm/arch-wokoo/wokoo_usbotg.h>


#ifdef CONFIG_USB_GADGET
static struct dwc2_plat_otg_data otg_data = {
	.rx_fifo_sz	= 512,
	.np_tx_fifo_sz	= 16,
	.tx_fifo_sz	= 128,
};
#endif

DECLARE_GLOBAL_DATA_PTR;

#if defined(CONFIG_WOKOO)
/* determine boot device from (BOOT_CFG[2:0]) */
u32 spl_boot_device(void)
{
	u32 vgpio0, vgpio1, vgpio2, mode;
	u32 bootmode = BOOT_DEVICE_NONE;

	gpio_direction_input(0);
	gpio_direction_input(1);
	gpio_direction_input(2);

	vgpio0 = gpio_get_value(0);
	vgpio1 = gpio_get_value(1);
	vgpio2 = gpio_get_value(2);

	mode   = ((vgpio2 & 0x1) << 2) + ((vgpio1 & 0x1) << 1) + (vgpio0 & 0x1);

	switch (mode) {
	case 0:
		bootmode = BOOT_DEVICE_UART;
		break;

#ifdef CONFIG_USB_GADGET
	case 1:
		/* USB OTG PHY init */
		wokoo_otg_phy_init();

		otg_data.regs_otg = CONFIG_USB_DWC2_REG_ADDR;
		dwc2_udc_probe(&otg_data);
		bootmode = BOOT_DEVICE_BOARD;
		break;
#endif

	case 2:
		bootmode = BOOT_DEVICE_SPI;
		break;

	case 3:
		bootmode = BOOT_DEVICE_SSI;
		break;
	}

	return bootmode;
}
#endif

#if defined(CONFIG_WOKOO) && defined(CONFIG_SPL_OS_BOOT)
int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = wokoo_ddr_size();

	return 0;
}
#endif
