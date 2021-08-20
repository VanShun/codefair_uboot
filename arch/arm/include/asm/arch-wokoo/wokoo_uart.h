/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_UART_H_
#define _WOKOO_UART_H_




struct wokoo_uart
{
	union {
		uint32_t RBR;	/*!< Offset: 0x0000   Receive Buffer Register */
		uint32_t THR;	/*!< Offset: 0x0000   Transmit Holding Register */
		uint32_t DLL;	/*!< Offset: 0x0000   Divisor Latch (Low) */
	};
	union {
		uint32_t DLH;	/*!< Offset: 0x0004   Divisor Latch (High) */
		uint32_t IER;	/*!< Offset: 0x0004   Interruput Enable Register */
	};
	union {
		uint32_t IIR;	/*!< Offset: 0x0008   Interruput Identification Register */
		uint32_t FCR;	/*!< Offset: 0x0008   FIFO Control Register */
	};
	uint32_t TCR;		/*!< Offset: 0x000C   Transmit Control Register */
	uint32_t MCR;		/*!< Offset: 0x0010   Modem Control Register */
	uint32_t TSR;		/*!< Offset: 0x0014   Transmit Status Register */
	uint32_t MSR;		/*!< Offset: 0x0018   Modem Status Register */
	uint32_t SCR;		/*!< Offset: 0x001C   Scratchpad Register */
	uint32_t LPDLL;		/*!< Offset: 0x0020   Low Power Divisor Latch Low */
	uint32_t LPDLH;		/*!< Offset: 0x0024   Low Power Divisor Latch High */
	uint32_t resv1[18];	/*!< Offset: 0x0028~0x006C reserved*/
	uint32_t FAR;		/*!< Offset: 0x0070   FIFO Access Register */
	uint32_t TFR;		/*!< Offset: 0x0074   Transmit FIFO Read */
	uint32_t RFW;		/*!< Offset: 0x0078   Receive FIFO Write */
	uint32_t USR;		/*!< Offset: 0x007C   UART Status Register */
	uint32_t TFL;		/*!< Offset: 0x0080  Transmit FIFO Level  */
	uint32_t RFL;		/*!< Offset: 0x0084   Receive FIFO Level */
	uint32_t SRR;		/*!< Offset: 0x0088  Software Reset Register  */
	uint32_t SRTS;		/*!< Offset: 0x008C  Shadow Request to Send  */
	uint32_t SBCR;		/*!< Offset: 0x0090   Shadow Break Control Register  */
	uint32_t SDMAM;		/*!< Offset: 0x0094  Shadow DMA Mode Register   */
	uint32_t SFE;		/*!< Offset: 0x0098	Shadow FIFO Enable Register    */
	uint32_t SRT;		/*!< Offset: 0x009C  Shadow RCVR Trigger Register  */
	uint32_t STET;		/*!< Offset: 0x00A0  Shadow TX Empty Trigger Register  */
	uint32_t HTX;		/*!< Offset: 0x00A4  Halt TX  */
	uint32_t DMASA;		/*!< Offset: 0x00A8 DMA Software Acknowledge Register   */
};

struct wokoo_serial_platdata {
	struct wokoo_uart *reg;  /* address of registers in physical memory */
};

#define UART_IER_ERBFI						(0x1UL << 0)
#define UART_IER_ETBEI						(0x1UL << 1)
#define UART_IER_ELSI						(0x1UL << 2)
#define UART_IER_EDSSI						(0x1UL << 3)
#define UART_IER_PTIME						(0x1UL << 7)

#define UART_IIR_IID_POS					(0)
#define UART_IIR_IID_MSK					(0x7UL << UART_IIR_IID_POS)
#define UART_IIR_FIFOSE_POS					(6)
#define UART_IIR_FIFOSE_MSK					(0x3UL << UART_IIR_FIFOSE_POS)

#define UART_FCR_FIFOE						(0x1UL << 0)
#define UART_FCR_RFIFOR						(0x1UL << 1)
#define UART_FCR_XFIFOR						(0x1UL << 2)
#define UART_FCR_TET_POS					(4)
#define UART_FCR_TET_MSK					(0x3UL << UART_FCR_TET_POS)
#define UART_FCR_RCVR_POS					(6)
#define UART_FCR_RCVR_MSK					(0x3UL << UART_FCR_RCVR_POS)

#define UART_TCR_DLS_POS					(0)
#define UART_TCR_DLS_MSK					(0x3UL << UART_TCR_DLS_POS)
#define UART_TCR_STOP						(0x1UL << 2)
#define UART_TCR_PEN						(0x1UL << 3)
#define UART_TCR_EPS						(0x1UL << 4)
#define UART_TCR_BC							(0x1UL << 6)
#define UART_TCR_DLAB						(0x1UL << 7)

#define UART_MCR_RTS						(0x1UL << 1)
#define UART_MCR_AFCE						(0x1UL << 5)

#define UART_TSR_DR							(0x1UL << 0)
#define UART_TSR_OE							(0x1UL << 1)
#define UART_TSR_PE							(0x1UL << 2)
#define UART_TSR_FE							(0x1UL << 3)
#define UART_TSR_BI							(0x1UL << 4)
#define UART_TSR_THRE						(0x1UL << 5)
#define UART_TSR_TEMT						(0x1UL << 6)
#define UART_TSR_RFE						(0x1UL << 7)

#define UART_MSR_DCTS						(0x1UL << 0)
#define UART_MSR_CTS						(0x1UL << 4)

#define UART_SCR_SCRMSK						(0xFFUL << 0)

#define UART_FAR_BIT						(0x1UL << 0)

#define UART_RFW_RFWD_POS					(0)
#define UART_RFW_RFWD_MSK					(0xFFUL << UART_RFW_RFWD_POS)
#define UART_RFW_RFPE						(0x1UL << 8)
#define UART_RFW_RFFE						(0x1UL << 9)

#define UART_USR_BUSY						(0x1UL << 0)

#define UART_SRR_UR							(0x1UL << 0)
#define UART_SRR_RFR						(0x1UL << 1)
#define UART_SRR_XFR						(0x1UL << 2)

#define UART_SRTS_BIT						(0x1UL << 0)

#define UART_SBCR_BIT						(0x1UL << 0)

#define UART_SDMAM_BIT						(0x1UL << 0)

#define UART_SFE_BIT						(0x1UL << 0)

#define UART_SRT_POS						(0)
#define UART_SRT_MSK						(0x3UL << UART_SRT_POS)

#define UART_STET_POS						(0)
#define UART_STET_MSK						(0x3UL << UART_STET_POS)

#define UART_HTX_BIT						(0x1UL << 0)

#define UART_DMASA_BIT						(0x1UL << 0)


#define UART_TCR_DLS_5BITS					(0x0UL << UART_TCR_DLS_POS)
#define UART_TCR_DLS_6BITS					(0x1UL << UART_TCR_DLS_POS)
#define UART_TCR_DLS_7BITS					(0x2UL << UART_TCR_DLS_POS)
#define UART_TCR_DLS_8BITS					(0x3UL << UART_TCR_DLS_POS)
#define UART_TCR_STOPBITS_1					((uint32_t)0x00000000)
#define UART_TCR_STOPBITS_1_5				((uint32_t)UART_TCR_STOP)
#define UART_TCR_STOPBITS_2					((uint32_t)UART_TCR_STOP)

#define UART_PARITY_NONE					((uint32_t)0x00000000)
#define UART_PARITY_EVEN					((uint32_t)(UART_TCR_PEN | UART_TCR_EPS))
#define UART_PARITY_ODD						((uint32_t)UART_TCR_PEN)

#define UART_1DIV_BAUDRATE					(115200 * 8)
#define UART_20XOSC_MUL						(576 * 8)
#define UART_1DIV_BAUDRATE_LOW_FREQ			(115200 * 4)
#define UART_20XOSC_MUL_LOW_FREQ			(576 * 4)
#define UART_20XOSC_DIV						(625)


#endif /* _WOKOO_UART_H_ */

