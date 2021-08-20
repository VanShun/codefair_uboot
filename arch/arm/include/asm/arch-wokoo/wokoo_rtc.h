/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_RTC_H_
#define _WOKOO_RTC_H_




struct wokoo_rtc
{
	uint32_t CCVR;      	/*!< Offset: 0x0000 current count value register */
	uint32_t CLR;       	/*!< Offset: 0x0004 counter initial value setting register */
	uint32_t CMR_ONE;   	/*!< Offset: 0x0008 timing match register 1 */
	uint32_t CMR_TWO;   	/*!< Offset: 0x000C timing match register 2 */
	uint32_t CMR_THREE; 	/*!< Offset: 0x0010 timing match register 3 */
	uint32_t ICR; 		 	/*!< Offset: 0x0014 interrupt control register */
	uint32_t ISR_EOI; 	 	/*!< Offset: 0x0018 interrupt clear register   */
	uint32_t WVR; 	 	 	/*!< Offset: 0x001C current week counter value register */
	uint32_t WLR; 	 	 	/*!< Offset: 0x0020 week counter initial value setting register */
	uint32_t RAW_LIMIT; 	/*!< Offset: 0x0024 counting frequency setting register */
	uint32_t SECOND_LIMIT;	/*!< Offset: 0x0028 second counting upper limit control register */
	uint32_t MINUTE_LIMIT;	/*!< Offset: 0x002C mintue counting upper limit control register */
	uint32_t HOUR_LIMIT; 	/*!< Offset: 0x0030 hour counting upper limit control register   */
	uint32_t ISR_RAW; 	 	/*!< Offset: 0x0034 interrupt raw status register  */
	uint32_t RVR; 	 		/*!< Offset: 0x0038 count value register in the current second */
	uint32_t PWEN_CTL;		/*!< Offset: 0x003C off-chip PMU control register*/
};



#define RTC_CCVR_SECOND_COUNT_POS 						(0)
#define RTC_CCVR_SECOND_COUNT_MSK 						(0x3FUL << RTC_CCVR_SECOND_COUNT_POS)
#define RTC_CCVR_MINUTE_COUNT_POS 						(6)
#define RTC_CCVR_MINUTE_COUNT_MSK 						(0x3FUL << RTC_CCVR_MINUTE_COUNT_POS)
#define RTC_CCVR_HOUR_COUNT_POS 						(12)
#define RTC_CCVR_HOUR_COUNT_MSK 						(0x1FUL << RTC_CCVR_HOUR_COUNT_POS)
#define RTC_CCVR_DAY_COUNT_POS 							(17)
#define RTC_CCVR_DAY_COUNT_MSK 							(0x7FFFUL << RTC_CCVR_DAY_COUNT_POS)

#define RTC_CLR_SECOND_COUNT_POS 						(0)
#define RTC_CLR_SECOND_COUNT_MSK 						(0x3FUL << RTC_CCVR_SECOND_COUNT_POS)
#define RTC_CLR_MINUTE_COUNT_POS 						(6)
#define RTC_CLR_MINUTE_COUNT_MSK 						(0x3FUL << RTC_CCVR_MINUTE_COUNT_POS)
#define RTC_CLR_HOUR_COUNT_POS 							(12)
#define RTC_CLR_HOUR_COUNT_MSK 							(0x1FUL << RTC_CCVR_HOUR_COUNT_POS)
#define RTC_CLR_DAY_COUNT_POS 							(17)
#define RTC_CLR_DAY_COUNT_MSK 							(0x7FFFUL << RTC_CCVR_DAY_COUNT_POS)

#define RTC_CMRX_SECOND_MATCH_POS 						(0)
#define RTC_CMRX_SECOND_MATCH_MSK 						(0x3FUL << RTC_CCVR_SECOND_COUNT_POS)
#define RTC_CMRX_MINUTE_MATCH_POS 						(6)
#define RTC_CMRX_MINUTE_MATCH_MSK 						(0x3FUL << RTC_CCVR_MINUTE_COUNT_POS)
#define RTC_CMRX_HOUR_MATCH_POS 						(12)
#define RTC_CMRX_HOUR_MATCH_MSK 						(0x1FUL << RTC_CCVR_HOUR_COUNT_POS)
#define RTC_CMRX_WEEK_MATCH_POS 						(17)
#define RTC_CMRX_WEEK_MATCH_SUN 						(0x1UL << 17)
#define RTC_CMRX_WEEK_MATCH_MON 						(0x1UL << 18)
#define RTC_CMRX_WEEK_MATCH_TUE 						(0x1UL << 19)
#define RTC_CMRX_WEEK_MATCH_WED 						(0x1UL << 20)
#define RTC_CMRX_WEEK_MATCH_THU 						(0x1UL << 21)
#define RTC_CMRX_WEEK_MATCH_FRI 						(0x1UL << 22)
#define RTC_CMRX_WEEK_MATCH_SAT 						(0x1UL << 23)

#define RTC_ICR_DAE 									(0x1UL << 0)
#define RTC_ICR_HOE 									(0x1UL << 1)
#define RTC_ICR_MIE 									(0x1UL << 2)
#define RTC_ICR_SEE 									(0x1UL << 3)
#define RTC_ICR_T2E 									(0x1UL << 4)
#define RTC_ICR_T1E 									(0x1UL << 5)
#define RTC_ICR_T3E 									(0x1UL << 6)
#define RTC_ICR_MASK 									(0x1UL << 7)
#define RTC_ICR_CNTE 									(0x1UL << 8)

#define RTC_ISR_DAF										(0x1UL << 0)
#define RTC_ISR_HOF 									(0x1UL << 1)
#define RTC_ISR_MIF 									(0x1UL << 2)
#define RTC_ISR_SEF 									(0x1UL << 3)
#define RTC_ISR_T2F 									(0x1UL << 4)
#define RTC_ISR_T1F 									(0x1UL << 5)
#define RTC_ISR_T3F 									(0x1UL << 6)

#define RTC_EOI_DA 										(0x1UL << 0)
#define RTC_EOI_HO 										(0x1UL << 1)
#define RTC_EOI_MI 										(0x1UL << 2)
#define RTC_EOI_SE 										(0x1UL << 3)
#define RTC_EOI_T2 										(0x1UL << 4)
#define RTC_EOI_T1 										(0x1UL << 5)
#define RTC_EOI_T3 										(0x1UL << 6)

#define RTC_WVR_MSK 									(0x7UL << 0)

#define RTC_WLR_MSK 									(0x7UL << 0)

#define RTC_RAW_LIMIT_MSK 								(0xFFFFUL << 0)

#define RTC_SECOND_LIMIT_MSK							(0x3FUL << 0)

#define RTC_MINUTE_LIMIT_MSK							(0x3FUL << 0)

#define RTC_HOUR_LIMIT_MSK								(0x1FUL << 0)

#define RTC_ISR_RAW_DAF 								(0x1UL << 0)
#define RTC_ISR_RAW_HOF 								(0x1UL << 1)
#define RTC_ISR_RAW_MIF 								(0x1UL << 2)
#define RTC_ISR_RAW_SEF 								(0x1UL << 3)
#define RTC_ISR_RAW_T2F 								(0x1UL << 4)
#define RTC_ISR_RAW_T1F 								(0x1UL << 5)
#define RTC_ISR_RAW_T3F 								(0x1UL << 6)

#define RTC_RVR_MSK 									(0xFFFFUL << 0)

#define RTC_PWEN_CTL0 									(0x1UL << 0)
#define RTC_PWEN_CTL1 									(0x1UL << 1)

#define WOKOO_RTC_BASE			0xA0156000


#endif /* _WOKOO_RTC_H_ */


