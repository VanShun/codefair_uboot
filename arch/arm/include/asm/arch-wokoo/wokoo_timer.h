/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_TIMER_H_
#define _WOKOO_TIMER_H_




struct wokoo_timer
{
	uint32_t TLC;	/*!< TIMERN LoadCount register,       Address offset: 0x00 + (N-1)*0x14 */
	uint32_t TCV;	/*!< TIMERN CurrentValue register,    Address offset: 0x04 + (N-1)*0x14 */
	uint32_t TCR;	/*!< TIMERN Control register,         Address offset: 0x08 + (N-1)*0x14 */
	uint32_t TIC;	/*!< TIMERN EOI register,             Address offset: 0x0c + (N-1)*0x14 */
	uint32_t TIS;	/*!< TIMERN InterruptStatus register, Address offset: 0x10 + (N-1)*0x14 */
};




#define WOKOO_TIMER_BASE			0x0A0149000


#endif /* _WOKOO_TIMER_H_ */

