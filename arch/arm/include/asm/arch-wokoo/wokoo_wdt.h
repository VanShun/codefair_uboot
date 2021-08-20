/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_WDT_H_
#define _WOKOO_WDT_H_




struct wokoo_wdt
{
	uint32_t CR;			/*!< Offset: 0x0000  control register */
	uint32_t TORR;			/*!< Offset: 0x0004  timeout range register */
	uint32_t CCVR;			/*!< Offset: 0x0008  current count register */
	uint32_t CRR;			/*!< Offset: 0x000C  counter restart register */
	uint32_t STAT;			  	/*!< Offset: 0x0010  interrupt status register */
	uint32_t ICR;			/*!< Offset: 0x0014  interrupt clear register */
};

#define WOKOO_WDT_BASE			0xA0148000


#endif /* _WOKOO_WDT_H_ */


