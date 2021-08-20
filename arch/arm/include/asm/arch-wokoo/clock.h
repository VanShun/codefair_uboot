/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H

#include <common.h>



enum wokoo_clock {
	WOKOO_ARM_CLK = 0,
	WOKOO_BUS_CLK,
	WOKOO_APB_CLK,
	WOKOO_UART_CLK,
	WOKOO_CSPI_CLK,
	WOKOO_AXI_CLK,
	WOKOO_DDR_CLK,
	WOKOO_I2C_CLK,
	WOKOO_USB_CLK,
};



u32 get_pllout(void);
u32 get_bus_clk(void);
unsigned int wokoo_get_clock(enum wokoo_clock clk);
void enable_ocotp_clk(unsigned char enable);
void enable_usbotg_clk(unsigned char enable);
void enable_wathchdog(unsigned char enable);
void enable_uart_clk(unsigned char enable, unsigned num);
int enable_usdhc_clk(unsigned char enable, unsigned bus_num);
int enable_i2c_clk(unsigned char enable, unsigned i2c_num);
int enable_spi_clk(unsigned char enable, unsigned spi_num);
void enable_qspi_clk(int qspi_num);
unsigned long get_uart_clk(unsigned num);
void set_bus_clk(u32 khz);
int enable_gtm_clk(unsigned char enable);
int set_gtm_clk(u32 parent, u32 clk);
void set_ddr_axi_clk(void);


void reset_ssi(void);
void set_ssi_protocol_mode(u32 mode);
void set_ssi_clk(u32 khz);
void set_apb_pclk(u32 khz);


#endif /* __ASM_ARCH_CLOCK_H */

