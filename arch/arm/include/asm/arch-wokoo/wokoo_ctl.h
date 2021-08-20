// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_CTL_H_
#define _WOKOO_CTL_H_




#define WOKOO_CTRL_BASE				0xA0060000

struct wokoo_ctl
{
	uint32_t reserved0[35];			/*!< Offset: 0x000~0x088  reserved register */
	uint32_t LP_MODE_CTRL;			/*!< Offset: 0x08C  CTL */
	uint32_t reserved1[37];			/*!< Offset: 0x090~0x120  reserved register */
	uint32_t RAM_EMA_CTRL;			/*!< Offset: 0x124  RAM EMA */
	uint32_t reserved2[3];			/*!< Offset: 0x128~0x130  reserved register*/
	uint32_t MH2X_CH_LP_EN;			/*!< Offset: 0x134  MH2X */
	uint32_t AP_DMAC_LP_EN;			/*!< Offset: 0x138  AP DMAC */
	uint32_t reserved2_5[5];		/*!< Offset: 0x13C~0x14C  reserved register*/
	uint32_t USB_OTG_PHY_RST_CTRL;	/*!< Offset: 0x150  USB OTG PHY */
	uint32_t USB_OTG_PHY_SUSPEND;	/*!< Offset: 0x154  USB OTG PHY suspend */
	uint32_t USB_OTG_PHY_STA;		/*!< Offset: 0x158  USB OTG PHY */
	uint32_t USB_OTG_WKUP_INTRAW;	/*!< Offset: 0x15C  USB OTG */
	uint32_t USB_OTG_WKUP_INTR_STA;	/*!< Offset: 0x160  USB OTG */
	uint32_t USB_OTG_WKUP_INTR_EN;	/*!< Offset: 0x164  USB OTG */
	uint32_t USB_OTG_PHY_CFG0;		/*!< Offset: 0x168  USB OTG PHY */
	uint32_t USB_OTG_PHY_CFG1;		/*!< Offset: 0x16C  USB OTG PHY */
	uint32_t reserved3[18];			/*!< Offset: 0x170~0x1B4  reserved register */
	uint32_t A7_CORE0_WBOOT_JUMP_ADDR;	/*!< Offset: 0x1B8  Cortex-A7 CORE0 */
	uint32_t reserved4[29];			/*!< Offset: 0x1BC~0x22C  reserved register*/
	uint32_t SSI0_PROTOCOL_CTRL;	/*!< Offset: 0x230  SSI0 */
	uint32_t reserved4_5;			/*!< Offset: 0x234  reserved register */
	uint32_t reserved5[10];			/*!< Offset: 0x238~0x25C  reserved register */
	uint32_t CPHY0_ERROR_STAT;		/*!< Offset: 0x260  ISP PHY0 */
	uint32_t reserved6;				/*!< Offset: 0x264  reserved register */
	uint32_t CPHY0_STAT;			/*!< Offset: 0x268  ISP PHY0 */
	uint32_t reserved7;				/*!< Offset: 0x26C  reserved register */
	uint32_t CPHY0_RSTZ;			/*!< Offset: 0x270  ISP PHY0 */
	uint32_t reserved8;				/*!< Offset: 0x274  reserved register */
	uint32_t CPHY0_CTRL0;			/*!< Offset: 0x278  ISP PHY0  */
	uint32_t CPHY0_CTRL1;			/*!< Offset: 0x27C  ISP PHY0 */
	uint32_t reserved9[2];			/*!< Offset: 0x280~0x284  reserved register */
	uint32_t CPHY0_MODE;			/*!< Offset: 0x288  ISP PHY0 */
	uint32_t reserved10;			/*!< Offset: 0x28C  reserved register */
	uint32_t A7_WBOOT_JUMP_ADDR1;	/*!< Offset: 0x290  Cortex-A7 */
	uint32_t A7_WBOOT_JUMP_ADDR2;	/*!< Offset: 0x294  Cortex-A7 */
	uint32_t A7_INTR_STA0;			/*!< Offset: 0x298  Cortex-A7 */
	uint32_t A7_INTR_STA1;			/*!< Offset: 0x29C  Cortex-A7 */
	uint32_t reserved11[8];			/*!< Offset: 0x2A0~0x2BC  reserved register */
	uint32_t A7_CFGTE;				/*!< Offset: 0x2C0  Cortex-A7 TE  */
	uint32_t reserved12[3];			/*!< Offset: 0x2C4~0x2CC  reserved register */
	uint32_t ISP_HIGH_ADDR;			/*!< Offset: 0x2D0  ISP */
};


#define CTL_LP_MODE_CTRL_LP_EN							(0x1UL << 0)
#define CTL_LP_MODE_CTRL_AHB_IDLE_LIMIT_POS				(8)
#define CTL_LP_MODE_CTRL_AHB_IDLE_LIMIT_MSK				(0xFFUL << CTL_LP_MODE_CTRL_AHB_IDLE_LIMIT_POS)

#define CTL_RAM_EMA_CTRL_CON							(0x1UL << 0)

#define CTL_MH2X_CH_LP_EN_ACP_MH2X_CH0_LP_EN			(0x1UL << 0)
#define CTL_MH2X_CH_LP_EN_ACP_MH2X_CH1_LP_EN			(0x1UL << 1)
#define CTL_MH2X_CH_LP_EN_ACP_MH2X_CH2_LP_EN			(0x1UL << 2)
#define CTL_MH2X_CH_LP_EN_ACP_MH2X_CH3_LP_EN			(0x1UL << 3)

#define CTL_AP_DMAC_LP_EN_ENABLE						(0x1UL << 0)

#define CTL_USB_OTG_PHY_RST_CTRL_USBPHY_RESET_N			(0x1UL << 0)
#define CTL_USB_OTG_PHY_RST_CTRL_USBPHY_PORT0_RESET_N	(0x1UL << 1)
#define CTL_USB_OTG_PHY_RST_CTRL_USBCTL_RESET_N			(0x1UL << 4)

#define CTL_USB_OTG_PHY_SUSPEND_USBPHY_SUSPEND_N		(0x1UL << 0)
#define CTL_USB_OTG_PHY_SUSPEND_USBPHY_SLEEP_N			(0x1UL << 1)

#define CTL_USB_OTG_PHY_STA_FSVPLUS 					(0x1UL << 0)
#define CTL_USB_OTG_PHY_STA_FSVMINUS					(0x1UL << 1)
#define CTL_USB_OTG_PHY_STA_LINESTATE_POS				(2)
#define CTL_USB_OTG_PHY_STA_LINESTATE_MSK				(0x3UL << CTL_USB_OTG_PHY_STA_LINESTATE_POS)

#define CTL_USB_OTG_WKUP_INTRAW_RAW						(0x1UL << 0)

#define CTL_USB_OTG_WKUP_INTR_STA_STATUS				(0x1UL << 0)

#define CTL_USB_OTG_WKUP_INTR_EN_ENABLE					(0x1UL << 0)

#define CTL_USB_OTG_PHY_CFG0_COMPDISTUNE_POS			(0)
#define CTL_USB_OTG_PHY_CFG0_COMPDISTUNE_MSK			(0x7UL << CTL_USB_OTG_PHY_CFG0_COMPDISTUNE_POS)
#define CTL_USB_OTG_PHY_CFG0_OTGTUNE0_POS				(4)
#define CTL_USB_OTG_PHY_CFG0_OTGTUNE0_MSK				(0x7UL << CTL_USB_OTG_PHY_CFG0_OTGTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_SQRXTUNE0_POS				(8)
#define CTL_USB_OTG_PHY_CFG0_SQRXTUNE0_MSK				(0x7UL << CTL_USB_OTG_PHY_CFG0_SQRXTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXFSLSTUNE0_POS			(12)
#define CTL_USB_OTG_PHY_CFG0_TXFSLSTUNE0_MSK			(0xFUL << CTL_USB_OTG_PHY_CFG0_TXFSLSTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXPREEMPAMPTUNE0_POS		(16)
#define CTL_USB_OTG_PHY_CFG0_TXPREEMPAMPTUNE0_MSK		(0x3UL << CTL_USB_OTG_PHY_CFG0_TXPREEMPAMPTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXPREEMPPULSETUNE0			(0x1UL << 18)
#define CTL_USB_OTG_PHY_CFG0_TXRISETUNE0_POS			(20)
#define CTL_USB_OTG_PHY_CFG0_TXRISETUNE0_MSK			(0x3UL << CTL_USB_OTG_PHY_CFG0_TXRISETUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXHSXVTUNE0_POS			(22)
#define CTL_USB_OTG_PHY_CFG0_TXHSXVTUNE0_MSK			(0x3UL << CTL_USB_OTG_PHY_CFG0_TXHSXVTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXVREFTUNE0_POS			(24)
#define CTL_USB_OTG_PHY_CFG0_TXVREFTUNE0_MSK			(0xFUL << CTL_USB_OTG_PHY_CFG0_TXVREFTUNE0_POS)
#define CTL_USB_OTG_PHY_CFG0_TXRESTUNE0_POS				(28)
#define CTL_USB_OTG_PHY_CFG0_TXRESTUNE0_MSK				(0x3UL << CTL_USB_OTG_PHY_CFG0_TXRESTUNE0_POS)

#define CTL_USB_OTG_PHY_CFG1_OTGDISABLE0				(0x1UL << 0)
#define CTL_USB_OTG_PHY_CFG1_SIDDQ						(0x1UL << 1)

#define CTL_A7_INTR_STA0_NIRQ0							(0x1UL << 0)
#define CTL_A7_INTR_STA0_NFIQ0							(0x1UL << 4)

#define CTL_A7_INTR_STA1_NCNTHPIRQ_POS					(0)
#define CTL_A7_INTR_STA1_NCNTHPIRQ_MSK					(0xFUL << CTL_A7_INTR_STA1_NCNTHPIRQ_POS)
#define CTL_A7_INTR_STA1_NCNTVIRQ_POS					(4)
#define CTL_A7_INTR_STA1_NCNTVIRQ_MSK					(0xFUL << CTL_A7_INTR_STA1_NCNTVIRQ_POS)
#define CTL_A7_INTR_STA1_NCNTPSIRQ_POS					(8)
#define CTL_A7_INTR_STA1_NCNTPSIRQ_MSK					(0xFUL << CTL_A7_INTR_STA1_NCNTPSIRQ_POS)
#define CTL_A7_INTR_STA1_NCNTPNSIRQ_POS					(12)
#define CTL_A7_INTR_STA1_NCNTPNSIRQ_MSK					(0xFUL << CTL_A7_INTR_STA1_NCNTPNSIRQ_POS)

#define CTL_A7_CFGTE_CON								(0x1UL << 0)

#define CTL_SSI0_PROTOCOL_CTRL_PRO						(0x1UL << 0)

#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRESC0				(0x1UL << 0)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRSYNCESC0			(0x1UL << 1)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTROL0			(0x1UL << 2)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP0		(0x1UL << 3)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP10	(0x1UL << 4)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTHS0			(0x1UL << 5)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTSYNCHS0		(0x1UL << 6)
#define CTL_CPHY0_ERROR_STAT_dPHY0_ERRESC1				(0x1UL << 8)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRSYNCESC1			(0x1UL << 9)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTROL1			(0x1UL << 10)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP01	(0x1UL << 11)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP11	(0x1UL << 12)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTHS1			(0x1UL << 13)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTSYNCHS1		(0x1UL << 14)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRESC2				(0x1UL << 16)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRSYNCESC2			(0x1UL << 17)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTROL2			(0x1UL << 18)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP02	(0x1UL << 19)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP12	(0x1UL << 20)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTHS2			(0x1UL << 21)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTSYNCHS2		(0x1UL << 22)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRESC3				(0x1UL << 24)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRSYNCESC3			(0x1UL << 25)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTROL3			(0x1UL << 26)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP03	(0x1UL << 27)
#define CTL_CPHY0_ERROR_STAT_DPHY0_ERRCONTENTIONLP13	(0x1UL << 28)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTHS3			(0x1UL << 29)
#define CTL_CPHY0_ERROR_STAT_CPHY0_ERRSOTSYNCHS3		(0x1UL << 30)

#define CTL_CPHY0_STAT_STOPSTATECLK						(0x1UL << 0)
#define CTL_CPHY0_STAT_RXULPSCLKNOT						(0x1UL << 1)
#define CTL_CPHY0_STAT_RXULPSESC0						(0x1UL << 8)
#define CTL_CPHY0_STAT_RXULPSESC1						(0x1UL << 9)
#define CTL_CPHY0_STAT_RXULPSESC2						(0x1UL << 10)
#define CTL_CPHY0_STAT_RXULPSESC3						(0x1UL << 11)
#define CTL_CPHY0_STAT_RXLPDTESC0						(0x1UL << 12)
#define CTL_CPHY0_STAT_RXLPDTESC1						(0x1UL << 13)
#define CTL_CPHY0_STAT_RXLPDTESC2						(0x1UL << 14)
#define CTL_CPHY0_STAT_RXLPDTESC3						(0x1UL << 15)
#define CTL_CPHY0_STAT_ULPSACTIVENOT0					(0x1UL << 16)
#define CTL_CPHY0_STAT_ULPSACTIVENOT1					(0x1UL << 17)
#define CTL_CPHY0_STAT_ULPSACTIVENOT2					(0x1UL << 18)
#define CTL_CPHY0_STAT_ULPSACTIVENOT3					(0x1UL << 19)
#define CTL_CPHY0_STAT_STOPSTATEDATA0					(0x1UL << 20)
#define CTL_CPHY0_STAT_STOPSTATEDATA1					(0x1UL << 21)
#define CTL_CPHY0_STAT_STOPSTATEDATA2					(0x1UL << 22)
#define CTL_CPHY0_STAT_STOPSTATEDATA3					(0x1UL << 23)

#define CTL_CPHY0_RSTZ_SHUTDOWNZ						(0x1UL << 0)
#define CTL_CPHY0_RSTZ_RSTZ								(0x1UL << 1)
#define CTL_CPHY0_RSTZ_ENABLECLK						(0x1UL << 2)
#define CTL_CPHY0_RSTZ_ENABLE_0							(0x1UL << 3)
#define CTL_CPHY0_RSTZ_ENABLE_1							(0x1UL << 4)
#define CTL_CPHY0_RSTZ_ENABLE_2							(0x1UL << 5)
#define CTL_CPHY0_RSTZ_ENABLE_3							(0x1UL << 6)

#define CTL_CPHY0_CTRL0_TESTCLR							(0x1UL << 0)
#define CTL_CPHY0_CTRL0_TESTCLK							(0x1UL << 1)

#define CTL_CPHY0_CTRL1_TESTDIN_POS						(0)
#define CTL_CPHY0_CTRL1_TESTDIN_MSK						(0xFFUL << CTL_CPHY0_CTRL1_TESTDIN_POS)
#define CTL_CPHY0_CTRL1_TESTOUT_POS						(8)
#define CTL_CPHY0_CTRL1_TESTOUT_MSK						(0xFFUL << CTL_CPHY0_CTRL1_TESTOUT_POS)
#define CTL_CPHY0_CTRL1_TESTEN							(0x1UL << 16)

#define CTL_CPHY0_MODE_TURNREQUEST						(0x1UL << 0)
#define CTL_CPHY0_MODE_TURNDISABLE						(0x1UL << 1)
#define CTL_CPHY0_MODE_FORCERXMODE						(0x1UL << 2)
#define CTL_CPHY0_MODE_FORCETXSTOPMODE					(0x1UL << 3)

#define CTL_ISP_HIGH_ADDR_ADDRESS_POS					(0)
#define CTL_ISP_HIGH_ADDR_ADDRESS_MSK					(0x3FFUL << CTL_ISP_HIGH_ADDR_ADDRESS_POS)
#define CTL_ISP_HIGH_ADDR_EN_POS						(16)
#define CTL_ISP_HIGH_ADDR_EN_MSK						(0x3FFUL << CTL_ISP_HIGH_ADDR_EN_POS)

#define WOKOO_CTL_BASE									0xA0060000




#endif /* _WOKOO_CTL_H_ */
