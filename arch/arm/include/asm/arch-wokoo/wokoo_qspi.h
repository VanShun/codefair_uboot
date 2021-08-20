/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_QSPI_H_
#define _WOKOO_QSPI_H_




struct wokoo_qspi_regs
{
	uint32_t CFG;		/*!< Offset: 0x00  QSPI Configuration Register */
	uint32_t DEVRD;		/*!< Offset: 0x04  Device Read Instruction Register */
	uint32_t DEVWR;		/*!< Offset: 0x08  Device Write Instruction Configuration Register */
	uint32_t DELAY;		/*!< Offset: 0x0C  QSPI Device Delay Register */
	uint32_t RDDATACAP;	/*!< Offset: 0x10  Read Data Capture Register */
	uint32_t DEVSZ;		/*!< Offset: 0x14  Device Size Configuration Register */
	uint32_t SRAMPART;	/*!< Offset: 0x18  SRAM Partition Configuration Register */
	uint32_t INDADDRTRIG;/*!< Offset: 0x1C  Indirect AHB Address Trigger register */
	uint32_t DMAPER;	/*!< Offset: 0x20  DMA Peripheral Configuration Register */
	uint32_t REMAPADDR;	/*!< Offset: 0x24  Remap Address Register */
	uint32_t MODEBIT;	/*!< Offset: 0x28  Mode Bit Configuration Register */
	uint32_t SRAMFILL;	/*!< Offset: 0x2C  SRAM Fill Level Register */
	uint32_t TTR;		/*!< Offset: 0x30  TX Threshold Register */
	uint32_t RTR;		/*!< Offset: 0x34  RX Threshold Register */
	uint32_t WCCR;		/*!< Offset: 0x38  Write Completion Control Register */
	uint32_t PER;		/*!< Offset: 0x3C  Polling Expiration Register */
	uint32_t ISR;		/*!< Offset: 0x40  Interrupt Status Register */
	uint32_t IMR;		/*!< Offset: 0x44  Interrupt Mask Register */
	uint32_t Reserved1;	/*!< Offset: 0x48  reserved Register */
	uint32_t Reserved2;	/*!< Offset: 0x4C  reserved Register */
	uint32_t LWPR;		/*!< Offset: 0x50  Lower Write Protection Register */
	uint32_t UWPR;		/*!< Offset: 0x54  Upper Write Protection Register */
	uint32_t WPR;		/*!< Offset: 0x58  Write Protection Register */
	uint32_t Reserved3;	/*!< Offset: 0x5C  reserved Register */
	uint32_t IRTCR;		/*!< Offset: 0x60  Indirect Read Transfer Control Register */
	uint32_t IRTWR;		/*!< Offset: 0x64  Indirect Read Transfer Watermark Register */
	uint32_t IRTSAR;	/*!< Offset: 0x68  Indirect Read Transfer Start Address Register */
	uint32_t IRTNBR;	/*!< Offset: 0x6C  Indirect Read Transfer Number Bytes Register */
	uint32_t IWTR;		/*!< Offset: 0x70  Indirect Write Transfer Control Register */
	uint32_t IWTWR;		/*!< Offset: 0x74  Indirect Write Transfer Watermark Register */
	uint32_t IWTSAR;	/*!< Offset: 0x78  Indirect Write Transfer Start Address Register */
	uint32_t IWTNBR;	/*!< Offset: 0x7C  Indirect Write Transfer Number Bytes Register */
	uint32_t ITARR;		/*!< Offset: 0x80  Indirect Trigger Address Range Register */
	uint32_t Reserved4;	/*!< Offset: 0x84  reserved Register */
	uint32_t Reserved5;	/*!< Offset: 0x88  reserved Register */
	uint32_t Reserved6;	/*!< Offset: 0x8C  reserved Register */
	uint32_t FCR;		/*!< Offset: 0x90  Flash Command Control Register (Using STIG) */
	uint32_t FCAR;		/*!< Offset: 0x94  Flash Command Address Register */
	uint32_t Reserved7; /*!< Offset: 0x98  reserved Register */
	uint32_t Reserved8; /*!< Offset: 0x9C  reserved Register */
	uint32_t FCRDRL;	/*!< Offset: 0xA0  Flash Command Read Data Register (Lower) */
	uint32_t FCRDRU;	/*!< Offset: 0xA4  Flash Command Read Data Register (Upper) */
	uint32_t FCWDRL;	/*!< Offset: 0xA8  Flash Command Write Data Register (Lower) */
	uint32_t FCWDRU;	/*!< Offset: 0xAC  Flash Command Write Data Register (Upper) */
	uint32_t PFSR;		/*!< Offset: 0xB0  Polling Flash Status Register */
	uint32_t Reserved9[18];/*!< Offset: 0xB4~0xF8  reserved Register */
	uint32_t MODULEID;	/*!< Offset: 0xFC  Module ID Register Register */
};


#define QSPI_CFG_ENABLE									(0x1UL << 0)
#define QSPI_CFG_CPOSW									(0x1UL << 1)
#define QSPI_CFG_CP										(0x1UL << 2)
#define QSPI_CFG_PME									(0x1UL << 3)
#define QSPI_CFG_EDAC									(0x1UL << 7)
#define QSPI_CFG_LIME									(0x1UL << 8)
#define QSPI_CFG_PSD									(0x1UL << 9)
#define QSPI_CFG_PCS_POS								(10)
#define QSPI_CFG_PCS_MSK								(0xFUL << QSPI_CFG_PCS_POS)
#define QSPI_CFG_STDTWP									(0x1UL << 14)
#define QSPI_CFG_EDPI									(0x1UL << 15)
#define QSPI_CFG_EAARMAP								(0x1UL << 16)
#define QSPI_CFG_EXMONREAD								(0x1UL << 17)
#define QSPI_CFG_EXM_IMMEDIATELY						(0x1UL << 18)
#define QSPI_CFG_MMBRD_POS								(19)
#define QSPI_CFG_MMBRD_MSK								(0xFUL << QSPI_CFG_MMBRD_POS)
#define QSPI_CFG_ENABLE_AHB_DECODER						(0x1UL << 23)
#define QSPI_CFG_ENABLE_DTR_PROTOCOL					(0x1UL << 24)
#define QSPI_CFG_PIPELINE_PHY_MODE_ENABLE				(0x1UL << 25)
#define QSPI_CFG_STATUS_IDLE							(0x1UL << 31)

#define QSPI_DEVRD_READ_OPCODE_POS						(0)
#define QSPI_DEVRD_READ_OPCODE_MSK						(0xFFUL << QSPI_DEVRD_READ_OPCODE_POS)
#define QSPI_DEVRD_INSTRUCTION_TYPE_POS					(8)
#define QSPI_DEVRD_INSTRUCTION_TYPE_MSK					(0x3UL << QSPI_DEVRD_INSTRUCTION_TYPE_POS)
#define QSPI_DEVRD_DDR_BIT_ENABLE						(0x1UL << 10)
#define QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS			(12)
#define QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_MSK			(0x3UL << QSPI_DEVRD_ADDRESS_TRANSFER_TYPE_POS)
#define QSPI_DEVRD_DATA_TRANSFER_TYPE_POS				(16)
#define QSPI_DEVRD_DATA_TRANSFER_TYPE_MSK				(0x3UL << QSPI_DEVRD_DATA_TRANSFER_TYPE_POS)
#define QSPI_DEVRD_MODE_BIT_ENABLE						(0x1UL << 20)
#define QSPI_DEVRD_READ_INSTRUCTION_POS					(24)
#define QSPI_DEVRD_READ_INSTRUCTION_MSK					(0x1FUL << QSPI_DEVRD_READ_INSTRUCTION_POS)

#define QSPI_DEVWR_WRITE_OPCODE_POS						(0)
#define QSPI_DEVWR_WRITE_OPCODE_MSK						(0xFFUL << QSPI_DEVWR_WRITE_OPCODE_POS)
#define QSPI_DEVWR_WEL_DISABLE							(0x1UL << 8)
#define QSPI_DEVWR_ADDRESS_TRANSFER_TYPE_POS			(12)
#define QSPI_DEVWR_ADDRESS_TRANSFER_TYPE_MSK			(0x3UL << QSPI_DEVWR_ADDRESS_TRANSFER_TYPE_POS)
#define QSPI_DEVWR_DATA_TRANSFER_TYPE_POS				(16)
#define QSPI_DEVWR_DATA_TRANSFER_TYPE_MSK				(0x3UL << QSPI_DEVWR_DATA_TRANSFER_TYPE_POS)
#define QSPI_DEVWR_WRITE_INSTRUCTION_POS				(24)
#define QSPI_DEVWR_WRITE_INSTRUCTION_MSK				(0x1FUL << QSPI_DEVWR_WRITE_INSTRUCTION_POS)

#define QSPI_DELAY_CSSOT_POS							(0)
#define QSPI_DELAY_CSSOT_MSK							(0xFFUL << QSPI_DELAY_CSSOT_POS)
#define QSPI_DELAY_CSEOT_POS							(8)
#define QSPI_DELAY_CSEOT_MSK							(0xFFUL << QSPI_DELAY_CSEOT_POS)
#define QSPI_DELAY_CSDADS_POS							(16)
#define QSPI_DELAY_CSDADS_MSK							(0xFFUL << QSPI_DELAY_CSDADS_POS)
#define QSPI_DELAY_CSDA_POS								(24)
#define QSPI_DELAY_CSDA_MSK								(0xFFUL << QSPI_DELAY_CSDA_POS)

#define QSPI_RDDATACAP_ENABLE_CLOCK						(0x1UL << 0)
#define QSPI_RDDATACAP_DELAY_READ_POS					(1)
#define QSPI_RDDATACAP_DELAY_READ_MSK					(0xFUL << QSPI_RDDATACAP_DELAY_READ_POS)
#define QSPI_RDDATACAP_SAMPLE_EDGE_SELECTION			(0x1UL << 5)
#define QSPI_RDDATACAP_DELAY_TRANSMITTED_POS			(16)
#define QSPI_RDDATACAP_DELAY_TRANSMITTED_MSK			(0xFUL << QSPI_RDDATACAP_DELAY_TRANSMITTED_POS)

#define QSPI_DEVSZ_ADDRESS_BYTES_POS					(0)
#define QSPI_DEVSZ_ADDRESS_BYTES_MSK					(0xFUL << QSPI_DEVSZ_ADDRESS_BYTES_POS)
#define QSPI_DEVSZ_DEVICE_PAGE_POS						(4)
#define QSPI_DEVSZ_DEVICE_PAGE_MSK						(0xFFFUL << QSPI_DEVSZ_DEVICE_PAGE_POS)
#define QSPI_DEVSZ_PER_BLCOK_POS						(16)
#define QSPI_DEVSZ_PER_BLCOK_MSK						(0x1FUL << QSPI_DEVSZ_PER_BLCOK_POS)
#define QSPI_DEVSZ_CONNECTED_CS0_POS					(21)
#define QSPI_DEVSZ_CONNECTED_CS0_MSK					(0x3UL << QSPI_DEVSZ_CONNECTED_CS0_POS)
#define QSPI_DEVSZ_CONNECTED_CS1_POS					(23)
#define QSPI_DEVSZ_CONNECTED_CS1_MSK					(0x3UL << QSPI_DEVSZ_CONNECTED_CS1_POS)
#define QSPI_DEVSZ_CONNECTED_CS2_POS					(25)
#define QSPI_DEVSZ_CONNECTED_CS2_MSK					(0x3UL << QSPI_DEVSZ_CONNECTED_CS2_POS)
#define QSPI_DEVSZ_CONNECTED_CS3_POS					(27)
#define QSPI_DEVSZ_CONNECTED_CS3_MSK					(0x3UL << QSPI_DEVSZ_CONNECTED_CS3_POS)

#define QSPI_SRAMPART_INDIRECT_READ_PARTITION_POS		(0)	//note
#define QSPI_SRAMPART_INDIRECT_READ_PARTITION_MSK		(0x3UL << QSPI_SRAMPART_INDIRECT_READ_PARTITION_POS)

#define QSPI_INDADDRTRIG_INDIRECT_TRIGGER_ADDRESS_POS	(0)
#define QSPI_INDADDRTRIG_INDIRECT_TRIGGER_ADDRESS_MSK	(0xFFFFFFFFUL << QSPI_INDADDRTRIG_INDIRECT_TRIGGER_ADDRESS_POS)

#define QSPI_DMAPER_SINGLE_TYPE_POS						(0)
#define QSPI_DMAPER_SINGLE_TYPE_MSK						(0xFUL << QSPI_DMAPER_SINGLE_TYPE_POS)
#define QSPI_DMAPER_BURST_TYPE_POS						(8)
#define QSPI_DMAPER_BURST_TYPE_MSK						(0xFUL << QSPI_DMAPER_BURST_TYPE_POS)

#define QSPI_REMAPADDR_AHB_ADDRESS_POS					(0)
#define QSPI_REMAPADDR_AHB_ADDRESS_MSK					(0xFFFFFFFFUL << QSPI_REMAPADDR_AHB_ADDRESS_POS)

#define QSPI_MODEBIT_ADDRESS_BYTES_POS					(0)
#define QSPI_MODEBIT_ADDRESS_BYTES_MSK					(0xFFUL << QSPI_MODEBIT_ADDRESS_BYTES_POS)

#define QSPI_SRAMFILL_READ_PARTITION_POS				(0)
#define QSPI_SRAMFILL_READ_PARTITION_MSK				(0xFFFFUL << QSPI_SRAMFILL_READ_PARTITION_POS)
#define QSPI_SRAMFILL_WRITE_PARTITION_POS				(15)
#define QSPI_SRAMFILL_WRITE_PARTITION_MSK				(0xFFFFUL << QSPI_SRAMFILL_WRITE_PARTITION_POS)

#define QSPI_TTR_TX_FIFO								(0x1UL << 0)

#define QSPI_RTR_RX_FIFO								(0x1UL << 0)

#define QSPI_WCCR_OPCODE_POS							(0)
#define QSPI_WCCR_OPCODE_MSK							(0xFFUL << QSPI_WCCR_OPCODE_POS)
#define QSPI_WCCR_POLLING_BIT_INDEX_POS					(8)
#define QSPI_WCCR_POLLING_BIT_INDEX_MSK					(0x7UL << QSPI_WCCR_POLLING_BIT_INDEX_POS)
#define QSPI_WCCR_POLLING_POLARITY						(0x1UL << 13)
#define QSPI_WCCR_DISABLE_POLLING						(0x1UL << 14)
#define QSPI_WCCR_POLLING_COUNT_POS						(16)
#define QSPI_WCCR_POLLING_COUNT_MSK						(0xFFUL << QSPI_WCCR_POLLING_COUNT_POS)
#define QSPI_WCCR_POLLING_DELAY_POS						(24)
#define QSPI_WCCR_POLLING_DELAY_MSK						(0xFFUL << QSPI_WCCR_POLLING_DELAY_POS)

#define QSPI_PER_POLLS_CYCLES_POS						(0)
#define QSPI_PER_POLLS_CYCLES_MSK						(0xFFFFFFFFUL << QSPI_PER_POLLS_CYCLES_POS)

#define QSPI_ISR_MODE_FAIL_M							(0x1UL << 0)
#define QSPI_ISR_UNDERFLOW_DETECTED						(0x1UL << 1)
#define QSPI_ISR_INDIRECT_OPERATION						(0x1UL << 2)
#define QSPI_ISR_NO_ACCEPTED							(0x1UL << 3)
#define QSPI_ISR_WRITE_TO_PROTECTED						(0x1UL << 4)
#define QSPI_ISR_ILLEGAL_AHB_ACCESS						(0x1UL << 5)
#define QSPI_ISR_LEVEL_BREACHED							(0x1UL << 6)
#define QSPI_ISR_RECEIVE_OVERFLOW						(0x1UL << 7)
#define QSPI_ISR_SMALL_TX_FIFO_EMPTY					(0x1UL << 8)
#define QSPI_ISR_SMALL_TX_FIFO_FULL						(0x1UL << 9)
#define QSPI_ISR_SMALL_RX_FIFO_EMPTY					(0x1UL << 10)
#define QSPI_ISR_SMALL_RX_FIFO_FULL						(0x1UL << 11)
#define QSPI_ISR_INDIRECT_READ_PARTITION				(0x1UL << 12)
#define QSPI_ISR_POLLS_CYCLES							(0x1UL << 13)

#define QSPI_IMR_INTERRUPT_STATUS_POS					(0)
#define QSPI_IMR_INTERRUPT_STATUS_MSK					(0x3FFUL << QSPI_IMR_INTERRUPT_STATUS_POS)

#define QSPI_LWPR_LOWER_WRITE_POS						(0)
#define QSPI_LWPR_LOWER_WRITE_MSK						(0xFFFFFFFFUL << QSPI_LWPR_LOWER_WRITE_POS)

#define QSPI_UWPR_UPPER_WRITE_POS						(0)
#define QSPI_UWPR_UPPER_WRITE_MSK						(0xFFFFFFFFUL << QSPI_UWPR_UPPER_WRITE_POS)

#define	QSPI_WPR_WRITE_EINVERSION						(0x1UL << 0)
#define	QSPI_WPR_WRITE_ENABLE							(0x1UL << 1)

#define	QSPI_IRTCR_START_INDIRECT_READ					(0x1UL << 0)
#define	QSPI_IRTCR_CANCEL_INDIRECT_READ					(0x1UL << 1)
#define	QSPI_IRTCR_INDIRECT_READ_OPERATION				(0x1UL << 2)
#define	QSPI_IRTCR_COMPLETE_INDIRECT_OPERATION			(0x1UL << 3)
#define	QSPI_IRTCR_TWO_INDIRECT_READ					(0x1UL << 4)
#define	QSPI_IRTCR_INDIRECT_COMPLETION_STATUS			(0x1UL << 5)
#define	QSPI_IRTCR_INDIRECT_NUMBER_POS					(6)
#define	QSPI_IRTCR_INDIRECT_NUMBER_MSK					(0x03UL << QSPI_IRTCR_INDIRECT_NUMBER_POS)

#define	QSPI_IRTWR_WATEMARK_VALUE_POS					(0)
#define	QSPI_IRTWR_WATEMARK_VALUE_MSK					(0xFFFFFFFFUL << QSPI_IRTWR_WATEMARK_VALUE_POS)

#define	QSPI_IRTSAR_INDIRECT_ACCESS_POS					(0)
#define	QSPI_IRTSAR_INDIRECT_ACCESS_MSK					(0xFFFFFFFFUL << QSPI_IRTSAR_INDIRECT_ACCESS_POS)

#define	QSPI_IRTNBR_INDIRECT_NUMBER_BYTTES_POS			(0)
#define	QSPI_IRTNBR_INDIRECT_NUMBER_BYTTES_MSK			(0xFFFFFFFFUL << QSPI_IRTNBR_INDIRECT_NUMBER_BYTTES_POS)

#define	QSPI_IWTR_START_INDIRECT_WRITE					(0x1UL << 0)
#define	QSPI_IWTR_CANCEL_INDIRECT_WRITE					(0x1UL << 1)
#define	QSPI_IWTR_INDIRECT_WRITE_OPERATION				(0x1UL << 2)
#define	QSPI_IWTR_TWO_INDIRECT_WRITE					(0x1UL << 4)
#define	QSPI_IWTR_INDIRECT_COMPLETION_STATUS			(0x1UL << 5)
#define	QSPI_IWTR_INDIRECT_NUMBER_POS					(6)
#define	QSPI_IWTR_INDIRECT_NUMBER_MSK					(0x03UL << QSPI_IWTR_INDIRECT_NUMBER_POS)

#define	QSPI_IWTWR_WATEMARK_VALUE_POS					(0)
#define	QSPI_IWTWR_WATEMARK_VALUE_MSK					(0xFFFFFFFFUL << QSPI_IWTWR_WATEMARK_VALUE_POS)

#define	QSPI_IWTSAR_INDIRECT_ACCESS_POS					(0)
#define	QSPI_IWTSAR_INDIRECT_ACCESS_MSK					(0xFFFFFFFFUL << QSPI_IWTSAR_INDIRECT_ACCESS_POS)

#define	QSPI_IWTNBR_INDIRECT_NUMBER_BYTTES_POS			(0)
#define	QSPI_IWTNBR_INDIRECT_NUMBER_BYTTES_MSK			(0xFFFFFFFFUL << QSPI_IWTNBR_INDIRECT_NUMBER_BYTTES_POS)

#define	QSPI_ITARR_INDIRECT_RANGE_WIDTH_POS				(0)
#define	QSPI_ITARR_INDIRECT_RANGE_WIDTH_MSK				(0xFUL << QSPI_ITARR_INDIRECT_RANGE_WIDTH_POS)

#define	QSPI_FCR_EXECUTE_THE_COMMAND					(0x1UL << 0)
#define	QSPI_FCR_COMMAND_EXECUTE_IN_PROGRESS			(0x1UL << 1)
#define	QSPI_FCR_DUMMY_BYTES_POS						(7)
#define	QSPI_FCR_DUMMY_BYTES_MSK						(0x1FUL << QSPI_FCR_DUMMY_BYTES_POS)
#define	QSPI_FCR_WRITE_DATA_BYTES_POS					(12)
#define	QSPI_FCR_WRITE_DATA_BYTES_MSK					(0x7UL << QSPI_FCR_WRITE_DATA_BYTES_POS)
#define	QSPI_FCR_WRITE_DATA_ENABLE						(0x1UL << 15)
#define	QSPI_FCR_ADDRESS_BYTES_POS						(16)
#define	QSPI_FCR_ADDRESS_BYTES_MSK						(0x3UL << QSPI_FCR_ADDRESS_BYTES_POS)
#define	QSPI_FCR_MODE_BIT_ENABLE						(0x1UL << 18)
#define	QSPI_FCR_COMMAND_ADDRESS_ENABLE					(0x1UL << 19)
#define	QSPI_FCR_READ_DATA_BYTES_POS					(20)
#define	QSPI_FCR_READ_DATA_BYTES_MSK					(0x7UL << QSPI_FCR_READ_DATA_BYTES_POS)
#define	QSPI_FCR_READ_DATA_ENABLE						(0x1UL << 23)
#define	QSPI_FCR_COMMAND_OPCODE_POS						(24)
#define	QSPI_FCR_COMMAND_OPCODE_MSK						(0xFFUL << QSPI_FCR_COMMAND_OPCODE_POS)

#define	QSPI_FCAR_COMMAND_ADDRESS_POS					(0)
#define	QSPI_FCAR_COMMAND_ADDRESS_MSK					(0xFFFFFFFFUL << QSPI_FCAR_COMMAND_ADDRESS_POS)

#define	QSPI_FCRDRL_READ_DATA_LOWER_BYTE_POS			(0)
#define	QSPI_FCRDRL_READ_DATA_LOWER_BYTE_MSK 			(0xFFFFFFFFUL << QSPI_FCRDRL_READ_DATA_LOWER_BYTE_POS)

#define	QSPI_FCRDRU_READ_DATA_UPPER_BYTE_POS			(0)
#define	QSPI_FCRDRU_READ_DATA_UPPER_BYTE_MSK			(0xFFFFFFFFUL << QSPI_FCRDRU_READ_DATA_UPPER_BYTE_POS)

#define	QSPI_FCWDRL_WRITE_DATA_LOWER_BYTE_POS			(0)
#define	QSPI_FCWDRL_WRITE_DATA_LOWER_BYTE_MSK			(0xFFFFFFFFUL << QSPI_FCWDRL_WRITE_DATA_LOWER_BYTE_POS)

#define	QSPI_FCWDRU_WRITE_DATA_UPPER_BYTE_POS			(0)
#define	QSPI_FCWDRU_WRITE_DATA_UPPER_BYTE_MSK			(0xFFFFFFFFUL << QSPI_FCWDRU_WRITE_DATA_UPPER_BYTE_POS)

#define	QSPI_PFSR_FLASH_STATUS_POS						(0)
#define	QSPI_PFSR_FLASH_STATUS_MSK						(0xFFUL << QSPI_PFSR_FLASH_STATUS_POS)
#define QSPI_PFSR_POLLING_STATUS_VALID					(0x1UL << 8)

/*
 * Commands
 */
#define QSPI_CMD_WRITE_ENABLE							0x06
#define QSPI_CMD_WRITE_DISABLE							0x04
#define QSPI_CMD_READ_IDENT								0x9F
#define QSPI_CMD_READ_STATUS							0x05
#define QSPI_CMD_WRITE_STATUS							0x01
#define QSPI_CMD_READ									0x03
#define QSPI_CMD_FAST_READ								0x0B
#define QSPI_CMD_PAGE_PROGRAM							0x02
#define QSPI_CMD_SECTOR_ERASE							0x20
#define QSPI_CMD_BULK_ERASE								0xC7
#define QSPI_CMD_BLOCK_4K_ERASE							0x20
#define QSPI_CMD_BLOCK_32K_ERASE						0x52
#define QSPI_CMD_ENTER_4B_MODE							0xB7
#define QSPI_CMD_EXIT_4B_MODE							0xE9

/* Quad 4B-addressing operations. */
#define QSPI_CMD_QUAD_SECTOR_ERASE						0xDC
#define QSPI_CMD_QUAD_PAGE_PROGRAM						0x34
#define QSPI_CMD_READ_4B_QUAD_OUTPUT					0x6C

/* Used for Spansion S25FS-S family flash only. */
#define QSPI_CMD_RDAR									0x65	/* Read any device register */
#define QSPI_CMD_WRAR									0x71	/* Write any device register */

#define QSPI_CMD_WRITE_QUAD								0x32
#define QSPI_CMD_READ_QUAD								0x6B

#define QSPI_CMD_SE										0xd8	/* Sector erase (usually 64KiB) */

/*
 * Status register flags
 */
#define QSPI_STATUS_SRWD								(1 << 7)
#define QSPI_STATUS_BP2									(1 << 4)
#define QSPI_STATUS_BP1									(1 << 3)
#define QSPI_STATUS_BP0									(1 << 2)
#define QSPI_STATUS_WEL									(1 << 1)
#define QSPI_STATUS_WIP									(1 << 0)

#define WOKOO_QSPI_MAP_ADDR								0xB0000000
#define WOKOO_QSPI_BASE_ADDR							0xA014E000



#endif /* _WOKOO_QSPI_H_ */

