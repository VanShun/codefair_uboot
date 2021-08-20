/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_GPIO_H_
#define _WOKOO_GPIO_H_



struct wokoo_gpio {
	uint32_t PORT_DR[8];			/*!< Offset: 0x000~0x01C  port data register */
	uint32_t PORT_DDR[8];			/*!< Offset: 0x020~0x03C  port data direction register */
	uint32_t EXT_PORT[4];			/*!< Offset: 0x040~0x04C  External port input register */
	uint32_t reserved0[44];			/*!< Offset: 0x050~0x0FC  reserved register*/
	uint32_t INTR_CTRL[32];			/*!< Offset: 0x100~0x17C  interrupt control register */
	uint32_t DEBOUNCE[8];			/*!< Offset: 0x180~0x19C  deburring enable register */
	uint32_t INTR_RAW[4];			/*!< Offset: 0x1A0~0x1AC  interrupt raw status register */
	uint32_t INTR_CLR[8];			/*!< Offset: 0x1B0~0x1BC  interrupt clear status register */
	uint32_t reserved1[16];			/*!< Offset: 0x1C0~0x1FC  reserved register*/
	uint32_t INTR_MASK_C0[8];		/*!< Offset: 0x200~0x21C  Cortex-A7 interrupt mask register */
	uint32_t INTR_STATUS_C0[4];		/*!< Offset: 0x220~0x22C  Cortex-A7 interrupt status register  */
};

#define WOKOO_GPIO_BASE				0xA014A000



#endif /* _WOKOO_GPIO_H_ */
