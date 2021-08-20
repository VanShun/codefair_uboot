/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_PWR_H_
#define _WOKOO_PWR_H_



struct wokoo_pwr
{
	/* Sleep related register */
	uint32_t SLPCTL0;			/*!< Offset: 0x000 Sleep Control Register 0 */
	uint32_t SLPCTL1;			/*!< Offset: 0x004 Sleep Control Register 1 */
	uint32_t SLPCNT_LIMIT;		/*!< Offset: 0x008 Sleep Entry Threshold Register */
	uint32_t SLPST;				/*!< Offset: 0x00C Sleep Enable Register */
	uint32_t PLLCR;				/*!< Offset: 0x010 PLL Timing Control Register */
	uint32_t SLPFSM_ST;			/*!< Offset: 0x014 Sleep State Machine Status Register */
	uint32_t reserve0[6];		/*!< Offset: 0x018~0x02C reserved */
	/* Clock related register */
	uint32_t PLLCTL0;			/*!< Offset: 0x030 PLL Configuration Register 0 */
	uint32_t PLLCTL1;			/*!< Offset: 0x034 PLL Configuration Register 1 */
	uint32_t reserve1[2];		/*!< Offset: 0x038~0x003C reserved */
	uint32_t A7_SYNC_CTL;		/*!< Offset: 0x040 Cortex-A7 Synchronization Control Register */
	uint32_t A7_CLK_CTL;		/*!< Offset: 0x044 Cortex-A7 Clock Control Register */
	uint32_t ADB_CLK_CTL;		/*!< Offset: 0x048 ADB Clock Control Register */
	uint32_t A7AXI_MAINCLK_CTL;	/*!< Offset: 0x04C A7_AXI Clock Control Register */
	uint32_t SYSCLK_CTL;		/*!< Offset: 0x050 System bus Clock Control Register */
	uint32_t SYSCLK_EN0;		/*!< Offset: 0x054 System bus Clock Enable Register 0 */
	uint32_t SYSCLK_EN1;		/*!< Offset: 0x058 System bus Clock Enable Register 1 */
	uint32_t SYSCLK_EN2;		/*!< Offset: 0x05C System bus Clock Enable Register 2 */
	uint32_t PLL_FREQ_CTL;		/*!< Offset: 0x060 PLL FM Control Register */
	uint32_t CTLPCLK_CTL;		/*!< Offset: 0x064 CTL APB Clock Control Register */
	uint32_t reserv2[2]; 		/*!< Offset: 0x068~0x06C  reserved */
	uint32_t UACRNGSLOW_CTL;	/*!< Offset: 0x070 UAC RNG SLOW Clock Control Register */
	uint32_t UAC_CLK_CTL;		/*!< Offset: 0x074 UAC Clock Control Register */
	uint32_t ARITHCLK_CTL;		/*!< Offset: 0x078 ARITH Clock Control Register */
	uint32_t ARITH_CLK_EN;		/*!< Offset: 0x07C ARITH Clock Enable Register */
	uint32_t DDRAXICLK_CTL;		/*!< Offset: 0x080 DDR_AXI Clock Control Register */
	uint32_t reserve4[2];		/*!< Offset: 0x084~0x088 reserved */
	uint32_t NFCCLK_EN;			/*!< Offset: 0x08C NFC Clock Enable Register */
	uint32_t USBCLKDIV_CTL;		/*!< Offset: 0x090 USB Frequency Division Control Register */
	uint32_t USBCLK_EN;			/*!< Offset: 0x094 USB Clock Enable Register */
	uint32_t reserve5;			/*!< Offset: 0x098 reserved*/
	uint32_t LCDCAXICLK_CTL;	/*!< Offset: 0x09C LCDC_AXI Clock Control Register */
	uint32_t LCDC0CLK_CTL;		/*!< Offset: 0x0A0 LCDC0 Clock Control Register */
	uint32_t reserve5_A[2];		/*!< Offset: 0x0A4~0x0A8 reserved */
	uint32_t ISPCLK_CTL0;		/*!< Offset: 0x0AC ISP Clock Control Register 0 */
	uint32_t ISPCLK_CTL1;		/*!< Offset: 0x0B0 ISP Clock Control Register 1 */
	uint32_t APBPCLK_EN0;		/*!< Offset: 0x0B4 APB Bus Clock Enable Register 0 */
	uint32_t APBPCLK_EN1;		/*!< Offset: 0x0B8 APB Bus Clock Enable Register 1 */
	uint32_t reserve6[2];		/*!< Offset: 0x0BC~0x0C0 reserved */
	uint32_t APBMCLK_EN;		/*!< Offset: 0x0C4 APB Working Clock Enable Register */
	uint32_t TIMER0CLKCTL;		/*!< Offset: 0x0C8 AP_TIMER0 Working Clock Control Register */
	uint32_t TIMER1CLKCTL;		/*!< Offset: 0x0CC AP_TIMER1 Working Clock Control Register */
	uint32_t TIMER2CLKCTL;		/*!< Offset: 0x0D0 AP_TIMER2 Working Clock Control Register */
	uint32_t TIMER3CLKCTL;		/*!< Offset: 0x0D4 AP_TIMER3 Working Clock Control Register */
	uint32_t PWMCLKDIV_CTL;		/*!< Offset: 0x0D8 PWM Frequency Division Control Register */
	uint32_t I2SCLKGR_CTL;		/*!< Offset: 0x0DC I2S Clock GR control register */
	uint32_t I2S0CLK_CTL;		/*!< Offset: 0x0E0 I2S0 Clock Control Register */
	uint32_t I2S1CLK_CTL;		/*!< Offset: 0x0E4 I2S1 Clock Control Register */
	uint32_t SSICLKGR_CTL;		/*!< Offset: 0x0E8 SSI Clock GR control register */
	uint32_t SSICLKDIV_CTL;		/*!< Offset: 0x0EC SSI Frequency Division Control Register */
	uint32_t UARTCLKGR_CTL;		/*!< Offset: 0x0F0 UART Clock GR control register */
	uint32_t UART0CLK_CTL;		/*!< Offset: 0x0F4 UART0 Clock Control Register */
	uint32_t UART1CLK_CTL;		/*!< Offset: 0x0F8 UART1 Clock Control Register */
	uint32_t UART2CLK_CTL;		/*!< Offset: 0x0FC UART2 Clock Control Register */
	uint32_t I2CCLK_CTL;		/*!< Offset: 0x100 I2C Clock Control Register */
	uint32_t reserve8[2];		/*!< Offset: 0x104~0x108 reserved */
	uint32_t reserve9[7];		/*!< Offset: 0x10C~0x124 reserved */
	uint32_t ATBCLK_CTL;		/*!< Offset: 0x128 ATB Clock Control Register */
	uint32_t A7DBGPCLK_CTL;		/*!< Offset: 0x12C A7_DBG_APB Clock Control Register */
	uint32_t CSCFGCLK_CTL;		/*!< Offset: 0x130 CS_CFG Clock Control Register */
	uint32_t CSCTMCLK_CTL;		/*!< Offset: 0x134 CS_CTM Clock Control Register */
	uint32_t reserve10[4];		/*!< Offset: 0x138~0x144 reserved */
	uint32_t CLKOUTSEL;			/*!< Offset: 0x148 CLKOUT Clock Select Register */
	uint32_t CLKOUT1CTL;		/*!< Offset: 0x14C CLKOUT1 Control Register */
	uint32_t CLKOUT2CLKCTL;		/*!< Offset: 0x150 CLKOUT2 Control Register */
	uint32_t CLKOUT3CLKCTL;		/*!< Offset: 0x154 CLKOUT3 Control Register */
	uint32_t TIMER4CLKCTL;		/*!< Offset: 0x158 AP_TIMER4 Working Clock Control Register */
	uint32_t TIMER5CLKCTL;		/*!< Offset: 0x15C AP_TIMER5 Working Clock Control Register */
	uint32_t TIMER6CLKCTL;		/*!< Offset: 0x160 AP_TIMER6 Working Clock Control Register */
	uint32_t reserve11[5];		/*!< Offset: 0x164~0x174 reserved */
	uint32_t CPCLK_CTL;			/*!< Offset: 0x178 CP Clock Control Register */
	uint32_t reserve11_5;		/*!< Offset: 0x17C reserved */
	/* Reset related registers */
	uint32_t SFRST_CTL;			/*!< Offset: 0x180 AP Soft Reset Control Register */
	uint32_t A7_RSTCTL0;		/*!< Offset: 0x184 Cortex-A7 Reset Control Register */
	uint32_t reserve12[2];		/*!< Offset: 0x188~0x18C reserved */
	uint32_t ARITH_RSTCTL;		/*!< Offset: 0x190 ARITH Reset Control Register */
	uint32_t ISP_RSTCTL;		/*!< Offset: 0x194 ISP Reset Control Register */
	uint32_t DISPLAY_RSTCTL;	/*!< Offset: 0x198 DISPLAY Reset Control Register */
	uint32_t COM_RSTCTL;		/*!< Offset: 0x19C COM Reset Control Register */
	uint32_t reserve13;			/*!< Offset: 0x1A0 reserved */
	uint32_t MOD_RSTCTL0;		/*!< Offset: 0x1A4 Module Soft Reset Control Register 0 */
	uint32_t MOD_RSTCTL1;		/*!< Offset: 0x1A8 Module Soft Reset Control Register 1 */
	uint32_t MOD_RSTCTL2;		/*!< Offset: 0x1AC Module Soft Reset Control Register 2 */
	uint32_t MOD_RSTCTL3;		/*!< Offset: 0x1B0 Module Soft Reset Control Register 3 */
	uint32_t MOD_RSTCTL4;		/*!< Offset: 0x1B4 Module Soft Reset Control Register 4 */
	uint32_t CS_RSTCTL;			/*!< Offset: 0x1B8 CORESIGHT Reset Control Register */
	uint32_t CHIPRSTN_CTL;		/*!< Offset: 0x1BC CHIP_RSTN Pin control register */
	uint32_t A7_RSTCTL1;		/*!< Offset: 0x1C0 Cortex-A7 Reset Control Register 1 */
	uint32_t A7_RSTCTL2;		/*!< Offset: 0x1C4 Cortex-A7 Reset Control Register 2 */
	uint32_t WDTRST_CTL;		/*!< Offset: 0x1C8 WDT Reset Control Register */
	uint32_t reserve14[5];		/*!< Offset: 0x1CC~0x1DC reserved */
	/* Interrupt related register */
	uint32_t A7INTIN_MK0;		/*!< Offset: 0x1E0 Cortex-A7 Interrupt Input Mask Register 0 */
	uint32_t A7INTIN_MK1;		/*!< Offset: 0x1E4 Cortex-A7 Interrupt Input Mask Register 1 */
	uint32_t reserve15[2];		/*!< Offset: 0x1E8~0x1EC reserved */
	uint32_t INT_RAW;			/*!< Offset: 0x1F0 Interrupt RAW Status Register */
	uint32_t INTST_A7;			/*!< Offset: 0x1F4 Cortex-A7 Interrupt Status Register */
	uint32_t INTEN_A7;			/*!< Offset: 0x1F8 Cortex-A7 Interrupt Enable Register */
	uint32_t reserve16[9];		/*!< Offset: 0x1FC~0x21C reserved */
	/* Power management related registers */
	uint32_t reserve17[34];		/*!< Offset: 0x220~0x2A4 reserved */
	uint32_t PWEN_CTL;			/*!< Offset: 0x2A8 PWEN Signal Control Register */
	uint32_t reserve18[9];		/*!< Offset: 0x2AC~0x2CC reserved */
	/* Other registers */
	uint32_t RESERVED_REG;		/*!< Offset: 0x2D0 Reserved Register */
	uint32_t reserve22[4];		/*!< Offset: 0x2D4~0x2E0 reserved */
	uint32_t LP_CTL;			/*!< Offset: 0x2E4 Low Power Control Register */
	uint32_t reserve23;			/*!< Offset: 0x2E8 reserved */
	uint32_t APB_DF_CTL;		/*!< Offset: 0x2EC APB Dynamic Frequency Control Register */
	uint32_t DDRAXI_DF_CTL;		/*!< Offset: 0x2F0 DDR_AXI Dynamic Frequency Control Register */
	uint32_t A7TSP_CTL;			/*!< Offset: 0x2F4 Cortex-A7 TSP Control Register */
	uint32_t A7_GTM_CTL;		/*!< Offset: 0x2F8 Cortex-A7 GTM Control Register */
	uint32_t reserve24;			/*!< Offset: 0x2FC reserved */
	uint32_t TM_CTL;			/*!< Offset: 0x300 Timer Counter Control Register */
	uint32_t TM_INIT_VAL;		/*!< Offset: 0x304 Timer Counter Inital Value Register */
	uint32_t TM_CUR_VAL;		/*!< Offset: 0x308 Timer Counter Current Value Register */
	uint32_t reserve25;			/*!< Offset: 0x30C reserved */
	uint32_t BUS_LP_CTL0;		/*!< Offset: 0x310 Bus Low Power Control Register 0 */
	uint32_t BUS_LP_CTL1;		/*!< Offset: 0x314 Bus Low Power Control Register 1 */
	uint32_t BUS_LP_CTL2;		/*!< Offset: 0x318 Bus Low Power Control Register 2 */
	uint32_t BUS_LP_CTL3;		/*!< Offset: 0x31C Bus Low Power Control Register 3 */
	uint32_t BUS_LP_CTL4;		/*!< Offset: 0x320 Bus Low Power Control Register 4 */
	uint32_t DEVICE_ST;			/*!< Offset: 0x324 Cortex-A7 Device status register */
	uint32_t BUS_LP_CTL5;		/*!< Offset: 0x328 Bus Low Power Control Register 5 */
};

#define PWR_SLPCTL0_A7C0_SLP_EN							(0x1UL << 0)
#define PWR_SLPCTL0_DMA_SLP_MK							(0x1UL << 5)
#define PWR_SLPCTL0_SLP_MK								(0x1UL << 6)
#define PWR_SLPCTL0_TOP_DDRAXI_SLP_MK					(0x1UL << 7)
#define PWR_SLPCTL0_CS_SLP_MK							(0x1UL << 8)
#define PWR_SLPCTL0_ADB_SLP_MK							(0x1UL << 12)
#define PWR_SLPCTL0_BIT_WE_A7C0_SLP_EN					(0x1UL << 16)
#define PWR_SLPCTL0_BIT_WE_DMA_SLP_MK					(0x1UL << 21)
#define PWR_SLPCTL0_BIT_WE_SLP_MK						(0x1UL << 22)
#define PWR_SLPCTL0_BIT_WE_TOP_DDRAXI_SLP_MK			(0x1UL << 23)
#define PWR_SLPCTL0_BIT_WE_CS_SLP_MK					(0x1UL << 24)
#define PWR_SLPCTL0_BIT_WE_ADB_SLP_MK					(0x1UL << 28)

#define PWR_SLPCTL1_TIMER_SYSCLK_SEL					(0x1UL << 0)
#define PWR_SLPCTL1_OSCEN_CTL							(0x1UL << 1)

#define PWR_SLPCNT_LIMIT_SLPCNT_CONFIG_NUM_POS			(0)
#define PWR_SLPCNT_LIMIT_SLPCNT_CONFIG_NUM_MSK			(0xFFFUL << PWR_SLPCNT_LIMIT_SLPCNT_CONFIG_NUM_POS)
#define PWR_SLPCNT_LIMIT_SYS_INTR_MK_NUM_POS			(12)
#define PWR_SLPCNT_LIMIT_SYS_INTR_MK_NUM_MSK			(0xFFUL << PWR_SLPCNT_LIMIT_SYS_INTR_MK_NUM_POS)

#define PWR_SLPST_SLP_ST								(0x1UL << 0)

#define PWR_PLLCR_OSC_ST_TIME_POS						(0)
#define PWR_PLLCR_OSC_ST_TIME_MSK						(0xFFUL << PWR_PLLCR_OSC_ST_TIME_POS)
#define PWR_PLLCR_PLL_ST_TIME_POS						(8)
#define PWR_PLLCR_PLL_ST_TIME_MSK						(0x7FUL << PWR_PLLCR_PLL_ST_TIME_POS)

#define PWR_SLPFSM_ST_AP_SLPFSM_ST_POS					(0)
#define PWR_SLPFSM_ST_AP_SLPFSM_ST_MSK					(0x7UL << PWR_SLPFSM_ST_AP_SLPFSM_ST_POS)

#define PWR_PLLCTL0_REFDIV_POS							(0)
#define PWR_PLLCTL0_REFDIV_MSK							(0x3FUL << PWR_PLLCTL0_REFDIV_POS)
#define PWR_PLLCTL0_FBDIV_POS							(8)
#define PWR_PLLCTL0_FBDIV_MSK							(0xFFFUL << PWR_PLLCTL0_FBDIV_POS)
#define PWR_PLLCTL0_POSTDIV1_POS						(20)
#define PWR_PLLCTL0_POSTDIV1_MSK						(0x7UL << PWR_PLLCTL0_POSTDIV1_POS)
#define PWR_PLLCTL0_POSTDIV2_POS						(24)
#define PWR_PLLCTL0_POSTDIV2_MSK						(0x7UL << PWR_PLLCTL0_POSTDIV2_POS)
#define PWR_PLLCTL0_DSMPD								(0x1UL << 28)

#define PWR_PLLCTL1_FRAC_POS							(0)
#define PWR_PLLCTL1_FRAC_MSK							(0xFFFFFF << PWR_PLLCTL1_FRAC_POS)
#define PWR_PLLCTL1_LOCK								(0x1UL << 24)

#define PWR_A7_SYNC_CTL_CLK_SEL							(0x1UL << 0)

#define PWR_A7_CLK_CTL_CLK_GR_POS						(0)
#define PWR_A7_CLK_CTL_CLK_GR_MSK						(0x1FUL << PWR_A7_CLK_CTL_CLK_GR_POS)
#define PWR_A7_CLK_CTL_PCLKDBG_GR_POS					(8)
#define PWR_A7_CLK_CTL_PCLKDBG_GR_MSK					(0xFUL << PWR_A7_CLK_CTL_PCLKDBG_GR_POS)
#define PWR_A7_CLK_CTL_ATCLK_GR_POS						(12)
#define PWR_A7_CLK_CTL_ATCLK_MSK						(0xFUL << PWR_A7_CLK_CTL_ATCLK_GR_POS)
#define PWR_A7_CLK_CTL_BIT_WE_CLK_GR					(0x1UL << 16)
#define PWR_A7_CLK_CTL_BIT_WE_PCLKDBG_GR				(0x1UL << 17)
#define PWR_A7_CLK_CTL_BIT_WE_ATCLK_GR					(0x1UL << 18)

#define PWR_ADB_CLK_CTL_ACLKS_SEL						(0x1UL << 0)
#define PWR_ADB_CLK_CTL_DFS_EN							(0x1UL << 1)
#define PWR_ADB_CLK_CTL_BIT_WE_ACLKS_SEL				(0x1UL << 16)
#define PWR_ADB_CLK_CTL_BIT_WE_DFS_EN					(0x1UL << 17)

#define PWR_A7AXI_MAINCLK_CTL_CLK_GR_POS				(0)
#define PWR_A7AXI_MAINCLK_CTL_CLK_GR_MSK				(0xFUL << PWR_A7AXI_MAINCLK_CTL_CLK_GR_POS)
#define PWR_A7AXI_MAINCLK_CTL_CLK_DR_POS				(4)
#define PWR_A7AXI_MAINCLK_CTL_CLK_DR_MSK				(0x3UL << PWR_A7AXI_MAINCLK_CTL_CLK_DR_POS)
#define PWR_A7AXI_MAINCLK_CTL_A7_AXI_GPV_CLK_EN			(0x1UL << 8)
#define PWR_A7AXI_MAINCLK_CTL_BIT_WE_CLK_GR				(0x1UL << 16)
#define PWR_A7AXI_MAINCLK_CTL_BIT_WE_CLK_DR				(0x1UL << 17)
#define PWR_A7AXI_MAINCLK_CTL_BIT_WE_A7_AXI_GPV_CLK_EN	(0x1UL << 18)

#define PWR_SYSCLK_CTL_BUS_MCLK_GR_POS					(0)
#define PWR_SYSCLK_CTL_BUS_MCLK_GR_MSK					(0xFUL << PWR_SYSCLK_CTL_BUS_MCLK_GR_POS)
#define PWR_SYSCLK_CTL_BUS_MCLK_DR_POS					(4)
#define PWR_SYSCLK_CTL_BUS_MCLK_DR_MSK					(0x3UL << PWR_SYSCLK_CTL_BUS_MCLK_DR_POS)
#define PWR_SYSCLK_CTL_BUS_MCLK_GR_WE					(0x1UL << 16)
#define PWR_SYSCLK_CTL_BUS_MCLK_DR_WE					(0x1UL << 17)

#define PWR_SYSCLK_EN0_PERI_BUS_CLK_EN					(0x1UL << 0)
#define PWR_SYSCLK_EN0_PERI_BUS_GPV_CLK_EN				(0x1UL << 1)
#define PWR_SYSCLK_EN0_DMA_AXI_CLK_EN					(0x1UL << 2)
#define PWR_SYSCLK_EN0_AXI_AHB_CLK_EN					(0x1UL << 4)
#define PWR_SYSCLK_EN0_AP_DMA_BUS_CLK_EN				(0x1UL << 5)
#define PWR_SYSCLK_EN0_AP_DMAG_CLK_EN					(0x1UL << 11)
#define PWR_SYSCLK_EN0_CTL_HCLK_EN						(0x1UL << 12)
#define PWR_SYSCLK_EN0_QSPI_HCLK_EN						(0x1UL << 13)
#define PWR_SYSCLK_EN0_BIT_WE_PERI_BUS_CLK_EN			(0x1UL << 16)
#define PWR_SYSCLK_EN0_BIT_WE_PERI_BUS_GPV_CLK_EN		(0x1UL << 17)
#define PWR_SYSCLK_EN0_BIT_WE_DMA_AXI_CLK_EN			(0x1UL << 18)
#define PWR_SYSCLK_EN0_BIT_WE_AXI_AHB_CLK_EN			(0x1UL << 20)
#define PWR_SYSCLK_EN0_BIT_WE_AP_DMA_BUS_CLK_EN			(0x1UL << 21)
#define PWR_SYSCLK_EN0_BIT_WE_AP_DMAG_CLK_EN			(0x1UL << 27)
#define PWR_SYSCLK_EN0_BIT_WE_CTL_HCLK_EN				(0x1UL << 28)
#define PWR_SYSCLK_EN0_BIT_WE_QSPI_HCLK_EN				(0x1UL << 29)


#define PWR_SYSCLK_EN1_USBOTG_HCLK_EN					(0x1UL << 0)
#define PWR_SYSCLK_EN1_SECURITY_HCLK_EN					(0x1UL << 3)
#define PWR_SYSCLK_EN1_SEC_RAM_HCLK_EN					(0x1UL << 4)
#define PWR_SYSCLK_EN1_CIPHER_HCLK_EN					(0x1UL << 5)
#define PWR_SYSCLK_EN1_BOOTROM_HCLK_EN					(0x1UL << 6)
#define PWR_SYSCLK_EN1_LCDC_HCLK_EN						(0x1UL << 7)
#define PWR_SYSCLK_EN1_UAC_HCLK_EN						(0x1UL << 8)
#define PWR_SYSCLK_EN1_PBR_HCLK_EN						(0x1UL << 9)
#define PWR_SYSCLK_EN1_A7_AXI_PERI_ACLK_EN				(0x1UL << 11)
#define PWR_SYSCLK_EN1_BIT_WE_USBOTG_HCLK_EN			(0x1UL << 16)
#define PWR_SYSCLK_EN1_BIT_WE_SECURITY_HCLK_EN			(0x1UL << 19)
#define PWR_SYSCLK_EN1_BIT_WE_SEC_RAM_HCLK_EN			(0x1UL << 20)
#define PWR_SYSCLK_EN1_BIT_WE_CIPHER_HCLK_EN			(0x1UL << 21)
#define PWR_SYSCLK_EN1_BIT_WE_BOOTROM_HCLK_EN			(0x1UL << 22)
#define PWR_SYSCLK_EN1_BIT_WE_LCDC_HCLK_EN				(0x1UL << 23)
#define PWR_SYSCLK_EN1_BIT_WE_UAC_HCLK_EN				(0x1UL << 24)
#define PWR_SYSCLK_EN1_BIT_WE_PBR_HCLK_EN				(0x1UL << 25)
#define PWR_SYSCLK_EN1_BIT_WE_A7_AXI_PERI_ACLK_EN		(0x1UL << 27)

#define PWR_SYSCLK_EN2_SYS_BUS_LP_CLK_EN				(0x1UL << 7)
#define PWR_SYSCLK_EN2_A7_AXI_BUS_LP_CLK_EN				(0x1UL << 8)
#define PWR_SYSCLK_EN2_DDR_AXI_BUS_LP_CLK_EN			(0x1UL << 11)
#define PWR_SYSCLK_EN2_ISP_BUS_LP_CLK_EN				(0x1UL << 12)
#define PWR_SYSCLK_EN2_BIT_WE_SYS_BUS_LP_CLK_EN			(0x1UL << 23)
#define PWR_SYSCLK_EN2_BIT_WE_A7_AXI_BUS_LP_CLK_EN		(0x1UL << 24)
#define PWR_SYSCLK_EN2_BIT_WE_DDR_AXI_BUS_LP_CLK_EN		(0x1UL << 27)
#define PWR_SYSCLK_EN2_BIT_WE_ISP_BUS_LP_CLK_EN			(0x1UL << 28)

#define PWR_PLL_FREQ_CTL_CHG_START						(0x1UL << 0)
#define PWR_PLL_FREQ_CTL_CHG_MK							(0x1UL << 1)
#define PWR_PLL_FREQ_CTL_BIT_WE_CHG_START				(0x1UL << 16)
#define PWR_PLL_FREQ_CTL_BIT_WE_CHG_MK					(0x1UL << 17)

#define PWR_APBPCLK_CTL_PCLK_DIV_WK_POS					(0)
#define PWR_APBPCLK_CTL_PCLK_DIV_WK_MSK					(0x7UL << PWR_APBPCLK_CTL_PCLK_DIV_WK_POS)
#define PWR_APBPCLK_CTL_PCLK_DIV_IDLE_POS				(4)
#define PWR_APBPCLK_CTL_PCLK_DIV_IDLE_MSK				(0x7UL << PWR_APBPCLK_CTL_PCLK_DIV_IDLE_POS)
#define PWR_APBPCLK_CTL_PCLK_DIV_WK_WE					(0x1UL << 16)
#define PWR_APBPCLK_CTL_PCLK_DIV_IDLE_WE				(0x1UL << 17)

#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_GR_POS			(0)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_GR_MSK			(0xFUL << PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_GR_POS)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_DIV_POS			(4)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_DIV_MSK			(0x1FUL << PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_DIV_POS)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_EN				(0x1UL << 12)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_GR_WE			(0x1UL << 16)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_DIV_WE			(0x1UL << 17)
#define PWR_UACRNGSLOW_CTL_UAC_RNG_SLOW_EN_WE			(0x1UL << 18)

#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_GR_POS				(0)
#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_GR_MSK				(0xFUL << PWR_UAC_CLK_CTL_UAC_SUB_CLK_GR_POS)
#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_DR_POS				(4)
#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_DR_MSK				(0x3UL << PWR_UAC_CLK_CTL_UAC_SUB_CLK_DR_POS)
#define PWR_UAC_CLK_CTL_UAC_ALG_CLK_EN					(0x1UL << 9)
#define PWR_UAC_CLK_CTL_UAC_HRNG_CLK_EN					(0x1UL << 11)
#define PWR_UAC_CLK_CTL_UAC_PKI_CLK_EN					(0x1UL << 12)
#define PWR_UAC_CLK_CTL_UAC_SM3_CLK_EN					(0x1UL << 14)
#define PWR_UAC_CLK_CTL_UAC_SM4_CLK_EN					(0x1UL << 15)
#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_GR_WE				(0x1UL << 16)
#define PWR_UAC_CLK_CTL_UAC_SUB_CLK_DR_WE				(0x1UL << 17)
#define PWR_UAC_CLK_CTL_UAC_ALG_CLK_EN_WE				(0x1UL << 19)
#define PWR_UAC_CLK_CTL_UAC_HRNG_CLK_EN_WE				(0x1UL << 21)
#define PWR_UAC_CLK_CTL_UAC_PKI_CLK_EN_WE				(0x1UL << 22)
#define PWR_UAC_CLK_CTL_UAC_SM3_CLK_EN_WE				(0x1UL << 24)
#define PWR_UAC_CLK_CTL_UAC_SM4_CLK_EN_WE				(0x1UL << 25)

#define PWR_ARITHCLK_CTL_ARITH_MCLK_GR_POS				(0)
#define PWR_ARITHCLK_CTL_ARITH_MCLK_GR_MSK				(0xFUL << PWR_ARITHCLK_CTL_ARITH_MCLK_GR_POS)
#define PWR_ARITHCLK_CTL_ARITH_MCLK_DR_POS				(4)
#define PWR_ARITHCLK_CTL_ARITH_MCLK_DR_MSK				(0x3UL << PWR_ARITHCLK_CTL_ARITH_MCLK_DR_POS)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_GR_POS				(8)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_GR_MSK				(0xFUL << PWR_ARITHCLK_CTL_ARITH_HCLK_GR_POS)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_DR_POS				(12)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_DR_MSK				(0x3UL << PWR_ARITHCLK_CTL_ARITH_HCLK_DR_POS)
#define PWR_ARITHCLK_CTL_ARITH_MCLK_GR_WE				(0x1UL << 16)
#define PWR_ARITHCLK_CTL_ARITH_MCLK_DR_WE				(0x1UL << 17)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_GR_WE				(0x1UL << 18)
#define PWR_ARITHCLK_CTL_ARITH_HCLK_DR_WE				(0x1UL << 19)

#define PWR_ARITH_CLK_EN_ARITH_MCLK_EN					(0x1UL << 4)
#define PWR_ARITH_CLK_EN_ARITH_MCLK_EN_WE				(0x1UL << 12)

#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_WK_POS			(0)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_WK_MSK			(0xFUL << PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_WK_POS)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_IDLE_POS		(4)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_IDLE_MSK		(0xFUL << PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_IDLE_POS)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_DR_POS			(8)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_DR_MSK			(0x3UL << PWR_DDRAXICLK_CTL_DDR_AXI_CLK_DR_POS)
#define PWR_DDRAXICLK_CTL_DDR_AXI_GPV_CLK_EN			(0x1UL << 12)
#define PWR_DDRAXICLK_CTL_2DACC_ACLK_EN					(0x1UL << 13)
#define PWR_DDRAXICLK_CTL_2DACC_ACLK_PROTECT_MK_EN		(0x1UL << 14)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_WK_WE			(0x1UL << 16)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_GR_IDLE_WE		(0x1UL << 17)
#define PWR_DDRAXICLK_CTL_DDR_AXI_CLK_DR_WE				(0x1UL << 18)
#define PWR_DDRAXICLK_CTL_DDR_AXI_GPV_CLK_EN_WE			(0x1UL << 19)
#define PWR_DDRAXICLK_CTL_2DACC_ACLK_EN_WE				(0x1UL << 20)
#define PWR_DDRAXICLK_CTL_2DACC_ACLK_PROTECT_MK_EN_WE	(0x1UL << 21)

#define PWR_NFCCLK_EN_ENABLE							(0x1UL << 0)
#define PWR_NFCCLK_EN_BIT_WE_ENABLE						(0x1UL << 8)

#define PWR_USBCLKDIV_CTL_USB_12M_DIV_POS				(0)
#define PWR_USBCLKDIV_CTL_USB_12M_DIV_MSK				(0x7UL << PWR_USBCLKDIV_CTL_USB_12M_DIV_POS)
#define PWR_USBCLKDIV_CTL_USB_12M_GR_POS				(3)
#define PWR_USBCLKDIV_CTL_USB_12M_GR_MSK				(0xFUL << PWR_USBCLKDIV_CTL_USB_12M_GR_POS)
#define PWR_USBCLKDIV_CTL_USB_CLK_SEL_POS				(7)
#define PWR_USBCLKDIV_CTL_USB_CLK_SEL_MSK				(0x3UL << PWR_USBCLKDIV_CTL_USB_CLK_SEL_POS)
#define PWR_USBCLKDIV_CTL_USB_FRE_SEL_POS				(9)
#define PWR_USBCLKDIV_CTL_USB_FRE_SEL_MSK				(0x7UL << PWR_USBCLKDIV_CTL_USB_FRE_SEL_POS)

#define PWR_USBCLK_EN_USBOTG_12M_EN 					(0x1UL << 0)
#define PWR_USBCLK_EN_USBOTG_BIT_WE_12M_EN				(0x1UL << 8)

#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_GR_POS			(0)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_GR_MSK			(0xFUL << PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_GR_POS)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_DR_POS			(4)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_DR_MSK			(0x3UL << PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_DR_POS)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_EN				(0x1UL << 8)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_GR_WE			(0x1UL << 16)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_DR_WE			(0x1UL << 17)
#define PWR_LCDCAXICLK_CTL_LCDC_AXI_CLK_EN_WE			(0x1UL << 18)

#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_GR_POS				(0)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_GR_MSK				(0xFUL << PWR_LCDC0CLK_CTL_LCDC0_MCLK_GR_POS)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_DIV_POS				(4)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_DIV_MSK				(0x1FUL << PWR_LCDC0CLK_CTL_LCDC0_MCLK_DIV_POS)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_EN					(0x1UL << 12)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_GR_WE				(0x1UL << 16)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_DIV_WE				(0x1UL << 17)
#define PWR_LCDC0CLK_CTL_LCDC0_MCLK_EN_WE				(0x1UL << 18)

#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_GR_POS				(0)
#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_GR_MSK				(0xFUL << PWR_ISPCLK_CTL0_ISP_AXI_CLK_GR_POS)
#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_DR_POS				(4)
#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_DR_MSK				(0x3UL << PWR_ISPCLK_CTL0_ISP_AXI_CLK_DR_POS)
#define PWR_ISPCLK_CTL0_ISP_P_SCLK_EN					(0x1UL << 8)
#define PWR_ISPCLK_CTL0_ISP_HCLK_EN						(0x1UL << 9)
#define PWR_ISPCLK_CTL0_LVDS_IDSP_SCLK_EN				(0x1UL << 10)
#define PWR_ISPCLK_CTL0_CPHY_CFG_CLK_EN					(0x1UL << 11)
#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_GR_WE				(0x1UL << 16)
#define PWR_ISPCLK_CTL0_ISP_AXI_CLK_DR_WE				(0x1UL << 17)
#define PWR_ISPCLK_CTL0_ISP_P_SCLK_EN_WE				(0x1UL << 18)
#define PWR_ISPCLK_CTL0_ISP_AHB_CLK_EN_WE				(0x1UL << 19)
#define PWR_ISPCLK_CTL0_LVDS_IDSP_SCLK_EN_WE			(0x1UL << 20)
#define PWR_ISPCLK_CTL0_CPHY_CFG_CLK_EN_WE				(0x1UL << 21)

#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_GR_POS			(0)
#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_GR_MSK			(0xFUL << PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_GR_POS)
#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_DR_POS			(4)
#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_DR_MSK			(0x3UL << PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_DR_POS)
#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_GR_WE			(0x1UL << 16)
#define PWR_ISPCLK_CTL1_ISP_PSCLK_SCLK2_DR_WE			(0x1UL << 17)

#define PWR_APBPCLK_EN0_I2S0_PCLK_EN					(0x1UL << 0)
#define PWR_APBPCLK_EN0_I2C0_PCLK_EN					(0x1UL << 1)
#define PWR_APBPCLK_EN0_I2C1_PCLK_EN					(0x1UL << 2)
#define PWR_APBPCLK_EN0_SSI0_PCLK_EN					(0x1UL << 3)
#define PWR_APBPCLK_EN0_UART0_PCLK_EN					(0x1UL << 4)
#define PWR_APBPCLK_EN0_UART1_PCLK_EN					(0x1UL << 5)
#define PWR_APBPCLK_EN0_UART2_PCLK_EN					(0x1UL << 6)
#define PWR_APBPCLK_EN0_PWM_PCLK_EN						(0x1UL << 7)
#define PWR_APBPCLK_EN0_WDT0_PCLK_EN					(0x1UL << 8)
#define PWR_APBPCLK_EN0_TIMERx_PCLK_EN					(0x1UL << 9)
#define PWR_APBPCLK_EN0_I2S1_PCLK_EN					(0x1UL << 10)
#define PWR_APBPCLK_EN0_GPIO0_PCLK_EN					(0x1UL << 11)
#define PWR_APBPCLK_EN0_QSPI_PCLK_EN					(0x1UL << 12)
#define PWR_APBPCLK_EN0_TPZCTL_PCLK_EN					(0x1UL << 13)
#define PWR_APBPCLK_EN0_RTC_PCLK_EN						(0x1UL << 14)
#define PWR_APBPCLK_EN0_BP147_PCLK_EN					(0x1UL << 15)
#define PWR_APBPCLK_EN0_BIT_WE_I2S0_PCLK_EN				(0x1UL << 16)
#define PWR_APBPCLK_EN0_BIT_WE_I2C0_PCLK_EN				(0x1UL << 17)
#define PWR_APBPCLK_EN0_BIT_WE_I2C1_PCLK_EN				(0x1UL << 18)
#define PWR_APBPCLK_EN0_BIT_WE_SSI0_PCLK_EN				(0x1UL << 19)
#define PWR_APBPCLK_EN0_BIT_WE_UART0_PCLK_EN			(0x1UL << 20)
#define PWR_APBPCLK_EN0_BIT_WE_UART1_PCLK_EN			(0x1UL << 21)
#define PWR_APBPCLK_EN0_BIT_WE_UART2_PCLK_EN			(0x1UL << 22)
#define PWR_APBPCLK_EN0_BIT_WE_PWM_PCLK_EN				(0x1UL << 23)
#define PWR_APBPCLK_EN0_BIT_WE_WDT0_PCLK_EN				(0x1UL << 24)
#define PWR_APBPCLK_EN0_BIT_WE_TIMERx_PCLK_EN			(0x1UL << 25)
#define PWR_APBPCLK_EN0_BIT_WE_I2S1_PCLK_EN				(0x1UL << 26)
#define PWR_APBPCLK_EN0_BIT_WE_GPIO0_PCLK_EN			(0x1UL << 27)
#define PWR_APBPCLK_EN0_BIT_WE_QSPI_PCLK_EN				(0x1UL << 28)
#define PWR_APBPCLK_EN0_BIT_WE_TPZCTL_PCLK_EN			(0x1UL << 29)
#define PWR_APBPCLK_EN0_BIT_WE_RTC_PCLK_EN				(0x1UL << 30)
#define PWR_APBPCLK_EN0_BIT_WE_BP147_PCLK_EN			(0x1UL << 31)

#define PWR_APBPCLK_EN1_MPHY_DDR_PCLK_EN				(0x1UL << 0)
#define PWR_APBPCLK_EN1_MCTL_DDR_PCLK_EN				(0x1UL << 1)
#define PWR_APBPCLK_EN1_MUXPIN_PCLK_EN					(0x1UL << 2)
#define PWR_APBPCLK_EN1_DDR_PWR_PCLK_EN					(0x1UL << 3)
#define PWR_APBPCLK_EN1_ISP_PCLK_EN						(0x1UL << 4)
#define PWR_APBPCLK_EN1_BIT_WE_MPHY_DDR_PCLK_EN			(0x1UL << 16)
#define PWR_APBPCLK_EN1_BIT_WE_MCTL_DDR_PCLK_EN			(0x1UL << 17)
#define PWR_APBPCLK_EN1_BIT_WE_MUXPIN_PCLK_EN			(0x1UL << 18)
#define PWR_APBPCLK_EN1_BIT_WE_DDR_PWR_PCLK_EN			(0x1UL << 19)
#define PWR_APBPCLK_EN1_BIT_WE_ISP_PCLK_EN				(0x1UL << 20)

#define PWR_APBMCLK_EN_I2C0_MCLK_EN						(0x1UL << 1)
#define PWR_APBMCLK_EN_I2C1_MCLK_EN						(0x1UL << 2)
#define PWR_APBMCLK_EN_PWM_MCLK_EN						(0x1UL << 4)
#define PWR_APBMCLK_EN_BIT_WE_I2C0_MCLK_EN				(0x1UL << 9)
#define PWR_APBMCLK_EN_BIT_WE_I2C1_MCLK_EN				(0x1UL << 10)
#define PWR_APBMCLK_EN_BIT_WE_PWM_MCLK_EN				(0x1UL << 12)

#define PWR_TIMERXCLKCTL_BUS_DIV_POS					(0)
#define PWR_TIMERXCLKCTL_BUS_DIV_MSK					(0xFFUL << PWR_TIMERXCLKCTL_BUS_DIV_POS)
#define PWR_TIMERXCLKCTL_PLL_DIV_POS					(8)
#define PWR_TIMERXCLKCTL_PLL_DIV_MSK					(0xFFUL << PWR_TIMERXCLKCTL_PLL_DIV_POS)
#define PWR_TIMERXCLKCTL_PBUS_DIV_POS					(16)
#define PWR_TIMERXCLKCTL_PBUS_DIV_MSK					(0xFFUL << PWR_TIMERXCLKCTL_PBUS_DIV_POS)
#define PWR_TIMERXCLKCTL_FUNC_DIV_POS					(24)
#define PWR_TIMERXCLKCTL_FUNC_DIV_MSK					(0xFUL << PWR_TIMERXCLKCTL_FUNC_DIV_POS)
#define PWR_TIMERXCLKCTL_SEL_POS						(28)
#define PWR_TIMERXCLKCTL_SEL_MSK						(0x7UL << PWR_TIMERXCLKCTL_SEL_POS)

#define PWR_PWMCLKDIV_CTL_PWM_CLK_DIV_POS				(0)
#define PWR_PWMCLKDIV_CTL_PWM_CLK_DIV_MSK				(0xFUL << PWR_PWMCLKDIV_CTL_PWM_CLK_DIV_POS)

#define PWR_I2SCLKGR_CTL_I2S0_CLK_GR_POS				(0)
#define PWR_I2SCLKGR_CTL_I2S0_CLK_GR_MSK				(0xFUL << PWR_I2SCLKGR_CTL_I2S0_CLK_GR_POS)
#define PWR_I2SCLKGR_CTL_I2S1_CLK_GR_POS				(4)
#define PWR_I2SCLKGR_CTL_I2S1_CLK_GR_MSK				(0xFUL << PWR_I2SCLKGR_CTL_I2S1_CLK_GR_POS)
#define PWR_I2SCLKGR_CTL_I2S0_CLK_GR_WE					(0x1UL << 16)
#define PWR_I2SCLKGR_CTL_I2S1_CLK_GR_WE					(0x1UL << 17)

#define PWR_I2SXCLK_CTL_DIV_POS							(0)
#define PWR_I2SXCLK_CTL_DIV_MSK							(0xFFFFUL << PWR_I2SXCLK_CTL_DIV_POS)
#define PWR_I2SXCLK_CTL_MUL_POS							(0)
#define PWR_I2SXCLK_CTL_MUL_MSK							(0xFFFFUL << PWR_I2SXCLK_CTL_MUL_POS)

#define PWR_SSICLKGR_CTL_SSI0_CLK_GR_POS				(0)
#define PWR_SSICLKGR_CTL_SSI0_CLK_GR_MSK				(0xFUL << PWR_SSICLKGR_CTL_SSI0_CLK_GR_POS)
#define PWR_SSICLKGR_CTL_SSI0_CLK_GR_WE					(0x1UL << 16)

#define PWR_SSICLKDIV_CTL_SSI0_CLK_DIV_POS				(0)
#define PWR_SSICLKDIV_CTL_SSI0_CLK_DIV_MSK				(0xFUL << PWR_SSICLKDIV_CTL_SSI0_CLK_DIV_POS)
#define PWR_SSICLKDIV_CTL_SSI0_CLK_DIV_WE				(0x1UL << 16)

#define PWR_UARTCLKGR_CTL_UART0_CLK_GR_POS				(0)
#define PWR_UARTCLKGR_CTL_UART0_CLK_GR_MSK				(0xFUL << PWR_UARTCLKGR_CTL_UART0_CLK_GR_POS)
#define PWR_UARTCLKGR_CTL_UART1_CLK_GR_POS				(4)
#define PWR_UARTCLKGR_CTL_UART1_CLK_GR_MSK				(0xFUL << PWR_UARTCLKGR_CTL_UART1_CLK_GR_POS)
#define PWR_UARTCLKGR_CTL_UART2_CLK_GR_POS				(8)
#define PWR_UARTCLKGR_CTL_UART2_CLK_GR_MSK				(0xFUL << PWR_UARTCLKGR_CTL_UART2_CLK_GR_POS)
#define PWR_UARTCLKGR_CTL_UART0_CLK_GR_WE				(0x1UL << 16)
#define PWR_UARTCLKGR_CTL_UART1_CLK_GR_WE				(0x1UL << 17)
#define PWR_UARTCLKGR_CTL_UART2_CLK_GR_WE				(0x1UL << 18)

#define PWR_UARTXCLK_CTL_DIV_POS						(0)
#define PWR_UARTXCLK_CTL_DIV_MSK						(0xFFFFUL << PWR_UARTXCLK_CTL_DIV_POS)
#define PWR_UARTXCLK_CTL_MUL_POS						(16)
#define PWR_UARTXCLK_CTL_MUL_MSK						(0xFFFFUL << PWR_UARTXCLK_CTL_MUL_POS)

#define PWR_I2CCLK_CTL_I2C0_CLK_DIV_POS					(0)
#define PWR_I2CCLK_CTL_I2C0_CLK_DIV_MSK					(0x1FUL << PWR_I2CCLK_CTL_I2C0_CLK_DIV_POS)
#define PWR_I2CCLK_CTL_I2C1_CLK_DIV_POS					(8)
#define PWR_I2CCLK_CTL_I2C1_CLK_DIV_MSK					(0x1FUL << PWR_I2CCLK_CTL_I2C1_CLK_DIV_POS)

#define PWR_ATBCLK_CTL_ATB_CLK_GR_POS					(0)
#define PWR_ATBCLK_CTL_ATB_CLK_GR_MSK					(0xFUL << PWR_ATBCLK_CTL_ATB_CLK_GR_POS)
#define PWR_ATBCLK_CTL_ATB_CLK_DR_POS					(4)
#define PWR_ATBCLK_CTL_ATB_CLK_DR_MSK					(0x3UL << PWR_ATBCLK_CTL_ATB_CLK_DR_POS)
#define PWR_ATBCLK_CTL_ATB_CLK_EN						(0x1UL << 8)
#define PWR_ATBCLK_CTL_ATB_CLK_GR_WE					(0x1UL << 16)
#define PWR_ATBCLK_CTL_ATB_CLK_DR_WE					(0x1UL << 17)
#define PWR_ATBCLK_CTL_ATB_CLK_EN_WE					(0x1UL << 18)

#define PWR_A7DBGPCLK_CTL_DBG_PCLK_EN					(0x1UL << 0)
#define PWR_A7DBGPCLK_CTL_DBG_PCLK_DIV_POS				(4)
#define PWR_A7DBGPCLK_CTL_DBG_PCLK_DIV_MSK				(0x7UL << PWR_A7DBGPCLK_CTL_DBG_PCLK_DIV_POS)
#define PWR_A7DBGPCLK_CTL_DBG_PCLK_EN_WE				(0x1UL << 16)
#define PWR_A7DBGPCLK_CTL_DBG_PCLK_DIV_WE				(0x1UL << 17)

#define PWR_CSCFGCLK_CTL_CS_CFGCLK_GR_POS				(0)
#define PWR_CSCFGCLK_CTL_CS_CFGCLK_GR_MSK				(0xFUL << PWR_CSCFGCLK_CTL_CS_CFGCLK_GR_POS)
#define PWR_CSCFGCLK_CTL_CS_CFGCLK_DR_POS				(4)
#define PWR_CSCFGCLK_CTL_CS_CFGCLK_DR_MSK				(0x3UL << PWR_CSCFGCLK_CTL_CS_CFGCLK_DR_POS)
#define PWR_CSCFGCLK_CTL_CS_CFGCLK_GR_WE				(0x1UL << 16)
#define PWR_CSCFGCLK_CTL_CS_CFGCLK_DR_WE				(0x1UL << 17)

#define PWR_CSCTMCLK_CTL_CTMCLK_GR_POS					(0)
#define PWR_CSCTMCLK_CTL_CTMCLK_GR_MSK					(0xFUL << PWR_CSCTMCLK_CTL_CTMCLK_GR_POS)
#define PWR_CSCTMCLK_CTL_CTMCLK_DR_POS					(4)
#define PWR_CSCTMCLK_CTL_CTMCLK_DR_MSK					(0x3UL << PWR_CSCTMCLK_CTL_CTMCLK_DR_POS)
#define PWR_CSCTMCLK_CTL_CTMCLK_GR_WE					(0x1UL << 16)
#define PWR_CSCTMCLK_CTL_CTMCLK_DR_WE					(0x1UL << 17)

#define PWR_CLKOUTSEL_CLKOUT1_SEL_POS					(0)
#define PWR_CLKOUTSEL_CLKOUT1_SEL_MSK					(0x7UL << PWR_CLKOUTSEL_CLKOUT1_SEL_POS)
#define PWR_CLKOUTSEL_CLKOUT2_SEL_POS					(4)
#define PWR_CLKOUTSEL_CLKOUT2_SEL_MSK					(0x7UL << PWR_CLKOUTSEL_CLKOUT2_SEL_POS)
#define PWR_CLKOUTSEL_CLKOUT3_SEL_POS					(8)
#define PWR_CLKOUTSEL_CLKOUT3_SEL_MSK					(0x7UL << PWR_CLKOUTSEL_CLKOUT3_SEL_POS)

#define PWR_CLKOUTXCTL_BUS_DIV_POS						(0)
#define PWR_CLKOUTXCTL_BUS_DIV_MSK						(0xFFUL << PWR_CLKOUTXCTL_BUS_DIV_POS)
#define PWR_CLKOUTXCTL_PLL_DIV0_POS						(8)
#define PWR_CLKOUTXCTL_PLL_DIV0_MSK						(0xFFUL << PWR_CLKOUTXCTL_PLL_DIV0_POS)
#define PWR_CLKOUTXCTL_PLL_DIV1_POS						(16)
#define PWR_CLKOUTXCTL_PLL_DIV1_MSK						(0xFFUL << PWR_CLKOUTXCTL_PLL_DIV1_POS)
#define PWR_CLKOUTXCTL_FUNC_DIV_POS						(24)
#define PWR_CLKOUTXCTL_FUNC_DIV_MSK						(0xFUL << PWR_CLKOUTXCTL_FUNC_DIV_POS)
#define PWR_CLKOUTXCTL_32K_DIV_POS						(28)
#define PWR_CLKOUTXCTL_32K_DIV_MSK						(0xFUL << PWR_CLKOUTXCTL_32K_DIV_POS)

#define PWR_CPCLK_CTL_CP_32K_EN							(0x1UL << 0)
#define PWR_CPCLK_BIT_WE_CTL_CP_32K_EN					(0x1UL << 8)

#define PWR_SFRST_CTL_CON_MSK							(0xFFUL << 0)

#define PWR_A7_RSTCTL0_A7C0_PO_RSTCTL					(0x1UL << 0)
#define PWR_A7_RSTCTL0_A7C0_RSTCTL						(0x1UL << 4)
#define PWR_A7_RSTCTL0_A7_DBG0_RSTCTL					(0x1UL << 8)
#define PWR_A7_RSTCTL0_A7_DBG1_RSTCTL					(0x1UL << 9)
#define PWR_A7_RSTCTL0_A7_ETM0_RSTCTL					(0x1UL << 12)
#define PWR_A7_RSTCTL0_A7_L2_RSTCTL						(0x1UL << 16)
#define PWR_A7_RSTCTL0_A7_SOCDBG_RSTCTL					(0x1UL << 17)

#define PWR_ARITH_RSTCTL_ARITH_HRESET_RSTCTL			(0x1UL << 4)

#define PWR_ISP_RSTCTL_ISP_AHB_RSTCTL					(0x1UL << 0)
#define PWR_ISP_RSTCTL_ISP_P_RSTCTL						(0x1UL << 1)

#define PWR_DISPLAY_RSTCTL_DISPLAY_RSTCTL				(0x1UL << 0)

#define PWR_COM_RSTCTL_COM_RSTCTL						(0x1UL << 0)
#define PWR_COM_RSTCTL_PWR_COM_RSTCTL					(0x1UL << 16)

#define PWR_MOD_RSTCTL0_PERI_AXI_RSTCTL					(0x1UL << 0)
#define PWR_MOD_RSTCTL0_ACP_AXI_RSTCTL					(0x1UL << 1)
#define PWR_MOD_RSTCTL0_DMA_AXI_RSTCTL					(0x1UL << 2)
#define PWR_MOD_RSTCTL0_DDR_AXI_RSTCTL					(0x1UL << 3)
#define PWR_MOD_RSTCTL0_AXI_AHB_RSTCTL					(0x1UL << 7)
#define PWR_MOD_RSTCTL0_AP_DMA_BUS_RSTCTL				(0x1UL << 8)
#define PWR_MOD_RSTCTL0_AP_DMAG_RSTCTL					(0x1UL << 9)
#define PWR_MOD_RSTCTL0_A7_AXI_MAIN_RSTCTL				(0x1UL << 10)
#define PWR_MOD_RSTCTL0_A7_AXI_GPV_RSTCTL				(0x1UL << 11)

#define PWR_MOD_RSTCTL1_CTL_RSTCTL						(0x1UL << 1)
#define PWR_MOD_RSTCTL1_QSPI_RSTCTL						(0x1UL << 2)
#define PWR_MOD_RSTCTL1_USBOTG_RSTCTL					(0x1UL << 5)
#define PWR_MOD_RSTCTL1_USBOTG_P_RSTCTL					(0x1UL << 6)
#define PWR_MOD_RSTCTL1_AP_SEC_RAM_RSTCTL				(0x1UL << 11)
#define PWR_MOD_RSTCTL1_CIPHER_RSTCTL					(0x1UL << 12)
#define PWR_MOD_RSTCTL1_BOOTROM_RSTCTL					(0x1UL << 13)
#define PWR_MOD_RSTCTL1_A7_AXI_PERI_RSTCTL				(0x1UL << 14)
#define PWR_MOD_RSTCTL1_UAC_RSTCTL						(0x1UL << 15)

#define PWR_MOD_RSTCTL2_RTC_RSTCTL						(0x1UL << 1)
#define PWR_MOD_RSTCTL2_TIMER0_RSTCTL					(0x1UL << 2)
#define PWR_MOD_RSTCTL2_TIMER1_RSTCTL					(0x1UL << 3)
#define PWR_MOD_RSTCTL2_TIMER2_RSTCTL					(0x1UL << 4)
#define PWR_MOD_RSTCTL2_TIMER3_RSTCTL					(0x1UL << 5)
#define PWR_MOD_RSTCTL2_I2C0_RSTCTL						(0x1UL << 6)
#define PWR_MOD_RSTCTL2_I2C1_RSTCTL						(0x1UL << 7)
#define PWR_MOD_RSTCTL2_GPIO0_RSTCTL					(0x1UL << 8)
#define PWR_MOD_RSTCTL2_PWM_RSTCTL						(0x1UL << 9)
#define PWR_MOD_RSTCTL2_TIMER4_RSTCTL					(0x1UL << 10)
#define PWR_MOD_RSTCTL2_TIMER5_RSTCTL					(0x1UL << 11)
#define PWR_MOD_RSTCTL2_TIMER6_RSTCTL					(0x1UL << 12)
#define PWR_MOD_RSTCTL2_WDT0_RSTCTL						(0x1UL << 13)

#define PWR_MOD_RSTCTL3_I2S0_RSTCTL						(0x1UL << 1)
#define PWR_MOD_RSTCTL3_I2S1_RSTCTL						(0x1UL << 2)
#define PWR_MOD_RSTCTL3_SSI0_RSTCTL						(0x1UL << 3)
#define PWR_MOD_RSTCTL3_UART0_RSTCTL					(0x1UL << 6)
#define PWR_MOD_RSTCTL3_UART1_RSTCTL					(0x1UL << 7)
#define PWR_MOD_RSTCTL3_UART2_RSTCTL					(0x1UL << 8)

#define PWR_MOD_RSTCTL4_MUXPIN_RSTCTL					(0x1UL << 1)
#define PWR_MOD_RSTCTL4_QSPI_RSTCTL						(0x1UL << 3)
#define PWR_MOD_RSTCTL4_BP147_RSTCTL					(0x1UL << 4)
#define PWR_MOD_RSTCTL4_TPZCTL_RSTCTL					(0x1UL << 5)

#define PWR_CS_RSTCTL_CS_ATB_RSTCTL						(0x1UL << 0)
#define PWR_CS_RSTCTL_CS_DBG_PM_RSTCTL					(0x1UL << 1)
#define PWR_CS_RSTCTL_CS_DBG_PS_RSTCTL					(0x1UL << 2)
#define PWR_CS_RSTCTL_CS_AHB_RSTCTL						(0x1UL << 3)
#define PWR_CS_RSTCTL_CS_CTM_RSTCTL						(0x1UL << 4)
#define PWR_CS_RSTCTL_CS_DBG_PRSTCTL					(0x1UL << 7)
#define PWR_CS_RSTCTL_CS_A7ATB40_RSTCTL					(0x1UL << 8)
#define PWR_CS_RSTCTL_CS_A7PRST50_RSTCTL				(0x1UL << 9)

#define PWR_CHIPRSTN_CTL_CHIP_RSTN_CNT_POS				(0)
#define PWR_CHIPRSTN_CTL_CHIP_RSTN_CNT_MSK				(0xFFFUL << PWR_CHIPRSTN_CTL_CHIP_RSTN_CNT_POS)
#define PWR_CHIPRSTN_CTL_CHIP_RSTN_MK					(0x1UL << 12)

#define PWR_A7_RSTCTL1_L1RSTDISABLE						(0x1UL << 0)
#define PWR_A7_RSTCTL1_L2RSTDISABLE						(0x1UL << 4)
#define PWR_A7_RSTCTL1_A7_SRST_CTL_POS					(8)
#define PWR_A7_RSTCTL1_A7_SRST_CTL_MSK					(0xFUL << PWR_A7_RSTCTL1_A7_SRST_CTL_POS)
#define PWR_A7_RSTCTL1_A7_RST_F_AU_DOWN_MK				(0x1UL << 12)
#define PWR_A7_RSTCTL1_WAIT_BUS_IDLE_MK					(0x1UL << 13)
#define PWR_A7_RSTCTL1_BIT_WE_L1RSTDISABLE				(0x1UL << 16)
#define PWR_A7_RSTCTL1_BIT_WE_L2RSTDISABLE				(0x1UL << 17)
#define PWR_A7_RSTCTL1_BIT_WE_A7_SRST_CTL				(0x1UL << 18)
#define PWR_A7_RSTCTL1_BIT_WE_A7_RST_F_AU_DOWN_MK		(0x1UL << 19)
#define PWR_A7_RSTCTL1_BIT_WE_WAIT_BUS_IDLE_MK			(0x1UL << 20)

#define PWR_A7_RSTCTL2_A7_SRST_TM_POS					(0)
#define PWR_A7_RSTCTL2_A7_SRST_TM_MSK					(0x3FUL << PWR_A7_RSTCTL2_A7_SRST_TM_POS)

#define PWR_WDTRST_CTL_PO_BY_WDT_POS					(0)
#define PWR_WDTRST_CTL_PO_BY_WDT_MSK					(0xFUL << PWR_WDTRST_CTL_PO_BY_WDT_POS)
#define PWR_WDTRST_CTL_WDT_RST_MD						(0x1UL << 4)
#define PWR_WDTRST_CTL_WDT_CLK_AUTO_OFF_EN				(0x1UL << 5)
#define PWR_WDTRST_CTL_BIT_WE_PO_BY_WDT					(0x1UL << 16)
#define PWR_WDTRST_CTL_BIT_WE_WDT_RST_MD				(0x1UL << 17)
#define PWR_WDTRST_CTL_BIT_WE_WDT_CLK_AUTO_OFF_EN		(0x1UL << 18)

#define PWR_A7INTIN_MK0_A7_INTIN_MK0					(0x1UL << 0)
#define PWR_A7INTIN_MK0_A7_INTIN_MK1					(0x1UL << 1)
#define PWR_A7INTIN_MK0_A7_INTIN_MK2					(0x1UL << 2)
#define PWR_A7INTIN_MK0_A7_INTIN_MK3					(0x1UL << 3)
#define PWR_A7INTIN_MK0_A7_INTIN_MK4					(0x1UL << 4)
#define PWR_A7INTIN_MK0_A7_INTIN_MK5					(0x1UL << 5)
#define PWR_A7INTIN_MK0_A7_INTIN_MK6					(0x1UL << 6)
#define PWR_A7INTIN_MK0_A7_INTIN_MK7					(0x1UL << 7)
#define PWR_A7INTIN_MK0_A7_INTIN_MK8					(0x1UL << 8)
#define PWR_A7INTIN_MK0_A7_INTIN_MK9					(0x1UL << 9)
#define PWR_A7INTIN_MK0_A7_INTIN_MK10					(0x1UL << 10)
#define PWR_A7INTIN_MK0_A7_INTIN_MK11					(0x1UL << 11)
#define PWR_A7INTIN_MK0_A7_INTIN_MK12					(0x1UL << 12)
#define PWR_A7INTIN_MK0_A7_INTIN_MK13					(0x1UL << 13)
#define PWR_A7INTIN_MK0_A7_INTIN_MK14					(0x1UL << 14)
#define PWR_A7INTIN_MK0_A7_INTIN_MK15					(0x1UL << 15)
#define PWR_A7INTIN_MK0_A7_INTIN_MK16					(0x1UL << 16)
#define PWR_A7INTIN_MK0_A7_INTIN_MK17					(0x1UL << 17)
#define PWR_A7INTIN_MK0_A7_INTIN_MK18					(0x1UL << 18)
#define PWR_A7INTIN_MK0_A7_INTIN_MK19					(0x1UL << 19)
#define PWR_A7INTIN_MK0_A7_INTIN_MK20					(0x1UL << 20)
#define PWR_A7INTIN_MK0_A7_INTIN_MK21					(0x1UL << 21)
#define PWR_A7INTIN_MK0_A7_INTIN_MK22					(0x1UL << 22)
#define PWR_A7INTIN_MK0_A7_INTIN_MK23					(0x1UL << 23)
#define PWR_A7INTIN_MK0_A7_INTIN_MK24					(0x1UL << 24)
#define PWR_A7INTIN_MK0_A7_INTIN_MK25					(0x1UL << 25)
#define PWR_A7INTIN_MK0_A7_INTIN_MK26					(0x1UL << 26)
#define PWR_A7INTIN_MK0_A7_INTIN_MK27					(0x1UL << 27)
#define PWR_A7INTIN_MK0_A7_INTIN_MK28					(0x1UL << 28)
#define PWR_A7INTIN_MK0_A7_INTIN_MK29					(0x1UL << 29)
#define PWR_A7INTIN_MK0_A7_INTIN_MK30					(0x1UL << 30)
#define PWR_A7INTIN_MK0_A7_INTIN_MK31					(0x1UL << 31)

#define PWR_A7INTIN_MK1_A7_INTIN_MK32					(0x1UL << 0)
#define PWR_A7INTIN_MK1_A7_INTIN_MK33					(0x1UL << 1)
#define PWR_A7INTIN_MK1_A7_INTIN_MK34					(0x1UL << 2)
#define PWR_A7INTIN_MK1_A7_INTIN_MK35					(0x1UL << 3)
#define PWR_A7INTIN_MK1_A7_INTIN_MK36					(0x1UL << 4)
#define PWR_A7INTIN_MK1_A7_INTIN_MK37					(0x1UL << 5)
#define PWR_A7INTIN_MK1_A7_INTIN_MK38					(0x1UL << 6)
#define PWR_A7INTIN_MK1_A7_INTIN_MK39					(0x1UL << 7)
#define PWR_A7INTIN_MK1_A7_INTIN_MK40					(0x1UL << 8)
#define PWR_A7INTIN_MK1_A7_INTIN_MK41					(0x1UL << 9)
#define PWR_A7INTIN_MK1_A7_INTIN_MK42					(0x1UL << 10)
#define PWR_A7INTIN_MK1_A7_INTIN_MK43					(0x1UL << 11)
#define PWR_A7INTIN_MK1_A7_INTIN_MK44					(0x1UL << 12)
#define PWR_A7INTIN_MK1_A7_INTIN_MK45					(0x1UL << 13)
#define PWR_A7INTIN_MK1_A7_INTIN_MK46					(0x1UL << 14)
#define PWR_A7INTIN_MK1_A7_INTIN_MK47					(0x1UL << 15)
#define PWR_A7INTIN_MK1_A7_INTIN_MK48					(0x1UL << 16)
#define PWR_A7INTIN_MK1_A7_INTIN_MK49					(0x1UL << 17)
#define PWR_A7INTIN_MK1_A7_INTIN_MK50					(0x1UL << 18)
#define PWR_A7INTIN_MK1_A7_INTIN_MK51					(0x1UL << 19)
#define PWR_A7INTIN_MK1_A7_INTIN_MK52					(0x1UL << 20)
#define PWR_A7INTIN_MK1_A7_INTIN_MK53					(0x1UL << 21)
#define PWR_A7INTIN_MK1_A7_INTIN_MK54					(0x1UL << 22)
#define PWR_A7INTIN_MK1_A7_INTIN_MK55					(0x1UL << 23)
#define PWR_A7INTIN_MK1_A7_INTIN_MK56					(0x1UL << 24)
#define PWR_A7INTIN_MK1_A7_INTIN_MK57					(0x1UL << 25)
#define PWR_A7INTIN_MK1_A7_INTIN_MK58					(0x1UL << 26)
#define PWR_A7INTIN_MK1_A7_INTIN_MK59					(0x1UL << 27)
#define PWR_A7INTIN_MK1_A7_INTIN_MK60					(0x1UL << 28)
#define PWR_A7INTIN_MK1_A7_INTIN_MK61					(0x1UL << 29)
#define PWR_A7INTIN_MK1_A7_INTIN_MK62					(0x1UL << 30)
#define PWR_A7INTIN_MK1_A7_INTIN_MK63					(0x1UL << 31)

#define PWR_INT_RAW_INTC_A7DBG_PU_RAW					(0x1UL << 2)
#define PWR_INT_RAW_INTC_A7_PU_RAW						(0x1UL << 3)
#define PWR_INT_RAW_INTC_ISP_PU_RAW						(0x1UL << 5)
#define PWR_INT_RAW_INTC_A7DBG_PD_RAW					(0x1UL << 10)
#define PWR_INT_RAW_INTC_A7_PD_RAW						(0x1UL << 11)
#define PWR_INT_RAW_INTC_ISP_PD_RAW						(0x1UL << 13)
#define PWR_INT_RAW_INTC_APWR_TM_RAW					(0x1UL << 16)
#define PWR_INT_RAW_INTC_CSPWRREQ_RAW					(0x1UL << 18)
#define PWR_INT_RAW_INTC_PLL_FC_RAW						(0x1UL << 21)

#define PWR_INTST_A7_INTC_A7DBG_PU_ST					(0x1UL << 2)
#define PWR_INTST_A7_INTC_A7_PU_ST						(0x1UL << 3)
#define PWR_INTST_A7_INTC_ISP_PU_ST						(0x1UL << 5)
#define PWR_INTST_A7_INTC_A7DBG_PD_ST					(0x1UL << 10)
#define PWR_INTST_A7_INTC_A7_PD_ST						(0x1UL << 11)
#define PWR_INTST_A7_INTC_ISP_PD_ST						(0x1UL << 13)
#define PWR_INTST_A7_INTC_APWR_TM_ST					(0x1UL << 16)
#define PWR_INTST_A7_INTC_CSPWRREQ_ST					(0x1UL << 18)
#define PWR_INTST_A7_INTC_PLL_FC_ST						(0x1UL << 21)

#define PWR_INTEN_A7_INTC_A7DBG_PU_EN					(0x1UL << 2)
#define PWR_INTEN_A7_INTC_A7_PU_EN						(0x1UL << 3)
#define PWR_INTEN_A7_INTC_ISP_PU_EN						(0x1UL << 5)
#define PWR_INTEN_A7_INTC_A7DBG_PD_EN					(0x1UL << 10)
#define PWR_INTEN_A7_INTC_A7_PD_EN						(0x1UL << 11)
#define PWR_INTEN_A7_INTC_ISP_PD_EN						(0x1UL << 13)
#define PWR_INTEN_A7_INTC_APWR_TM_EN					(0x1UL << 16)
#define PWR_INTEN_A7_INTC_CSPWRREQ_EN					(0x1UL << 18)
#define PWR_INTEN_A7_INTC_PLL_FC_EN						(0x1UL << 21)


#define PWR_PWEN_CTL_PWEN_CTL							(0x1UL << 0)

#define PWR_RESERVED_REG_A7_PU_FREQ_AUTO_CHG_EN			(0x1UL << 1)
#define PWR_RESERVED_REG_SLP_A7_PD_EN					(0x1UL << 2)

#define PWR_LP_CTL_CTL_PCLK_LP_EN						(0x1UL << 0)
#define PWR_LP_CTL_DATA_PCLK_LP_EN						(0x1UL << 1)
#define PWR_LP_CTL_UART0_CLK_OFF_PROTECT_EN				(0x1UL << 2)
#define PWR_LP_CTL_UART1_CLK_OFF_PROTECT_EN				(0x1UL << 3)
#define PWR_LP_CTL_UART2_CLK_OFF_PROTECT_EN				(0x1UL << 4)
#define PWR_LP_CTL_AHB_BUS_LP_EN						(0x1UL << 8)
#define PWR_LP_CTL_ICM_LP_EN							(0x1UL << 9)
#define PWR_LP_CTL_DDR_AXI_LP_EN						(0x1UL << 10)
#define PWR_LP_CTL_SLP_RAM_LP_MODE_POS					(16)
#define PWR_LP_CTL_SLP_RAM_LP_MODE_MSK					(0x3UL << PWR_LP_CTL_SLP_RAM_LP_MODE_POS)

#define PWR_APB_DF_CTL_DFSW_NUM_POS						(0)
#define PWR_APB_DF_CTL_DFSW_NUM_MSK						(0xFFUL << PWR_APB_DF_CTL_DFSW_NUM_POS)
#define PWR_APB_DF_CTL_DFSW_NUM_WE						(0x1UL << 16)

#define PWR_DDRAXI_DF_CTL_DDR_AXI_DFSW_NUM_POS			(0)
#define PWR_DDRAXI_DF_CTL_DDR_AXI_DFSW_NUM_MSK			(0xFFFUL << PWR_DDRAXI_DF_CTL_DDR_AXI_DFSW_NUM_POS)

#define PWR_A7TSP_CTL_A7TSP_CLK_EN						(0x1UL << 0)
#define PWR_A7TSP_CTL_A7TSP_RSTCTL						(0x1UL << 1)
#define PWR_A7TSP_CTL_A7TSP_ENABLE						(0x1UL << 2)
#define PWR_A7TSP_CTL_BIT_WE_A7TSP_CLK_EN				(0x1UL << 16)
#define PWR_A7TSP_CTL_BIT_WE_A7TSP_RSTCTL				(0x1UL << 17)
#define PWR_A7TSP_CTL_BIT_WE_A7TSP_ENABLE				(0x1UL << 18)

#define PWR_A7_GTM_CTL_CLK_EN							(0x1UL << 0)
#define PWR_A7_GTM_CTL_CLK_SRC_SEL						(0x1UL << 1)
#define PWR_A7_GTM_CTL_STATE_CTL						(0x1UL << 2)
#define PWR_A7_GTM_CTL_CS_HLTDBG_MK						(0x1UL << 3)
#define PWR_A7_GTM_CTL_CLK_DIV_POS						(8)
#define PWR_A7_GTM_CTL_CLK_DIV_MSK						(0xFFUL << PWR_A7_GTM_CTL_CLK_DIV_POS)
#define PWR_A7_GTM_CTL_BIT_WE_CLK_EN					(0x1UL << 16)
#define PWR_A7_GTM_CTL_BIT_WE_CLK_SRC_SEL				(0x1UL << 17)
#define PWR_A7_GTM_CTL_BIT_WE_STATE_CTL					(0x1UL << 18)
#define PWR_A7_GTM_CTL_BIT_WE_CS_HLTDBG_MK				(0x1UL << 19)
#define PWR_A7_GTM_CTL_BIT_WE_CLK_DIV					(0x1UL << 20)

#define PWR_TM_CTL_TM_WK_MODE							(0x1UL << 0)
#define PWR_TM_CTL_TM_LD_MODE							(0x1UL << 1)
#define PWR_TM_CTL_TM_EN								(0x1UL << 2)
#define PWR_TM_CTL_TM_ST								(0x1UL << 3)
#define PWR_TM_CTL_BIT_WE_TM_WK_MODE					(0x1UL << 8)
#define PWR_TM_CTL_BIT_WE_TM_LD_MODE					(0x1UL << 9)
#define PWR_TM_CTL_BIT_WE_TM_EN							(0x1UL << 10)

#define PWR_BUS_LP_CTL0_PERI_AXI_MAIN_LP_EN				(0x1UL << 0)
#define PWR_BUS_LP_CTL0_PERI_AXI_CIPHER_LP_EN			(0x1UL << 1)
#define PWR_BUS_LP_CTL0_PERI_AXI_SECURITY_LP_EN			(0x1UL << 2)
#define PWR_BUS_LP_CTL0_PERI_AXI_SEC_RAM_LP_EN			(0x1UL << 3)
#define PWR_BUS_LP_CTL0_PERI_AXI_AHB_LP_EN				(0x1UL << 4)
#define PWR_BUS_LP_CTL0_PERI_AXI_DMA_AXI_S1_LP_EN		(0x1UL << 5)
#define PWR_BUS_LP_CTL0_PERI_AXI_MAIN_LP_LMT_POS		(8)
#define PWR_BUS_LP_CTL0_PERI_AXI_MAIN_LP_LMT_MSK		(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_MAIN_LP_LMT_POS)
#define PWR_BUS_LP_CTL0_PERI_AXI_CIPHER_LP_LMT_POS		(12)
#define PWR_BUS_LP_CTL0_PERI_AXI_CIPHER_LP_LMT_MSK		(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_CIPHER_LP_LMT_POS)
#define PWR_BUS_LP_CTL0_PERI_AXI_SECURITY_LP_LMT_POS	(16)
#define PWR_BUS_LP_CTL0_PERI_AXI_SECURITY_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_SECURITY_LP_LMT_POS)
#define PWR_BUS_LP_CTL0_PERI_AXI_SEC_RAM_LP_LMT_POS		(20)
#define PWR_BUS_LP_CTL0_PERI_AXI_SEC_RAM_LP_LMT_MSK		(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_SEC_RAM_LP_LMT_POS)
#define PWR_BUS_LP_CTL0_PERI_AXI_AHB_LP_LMT_POS			(24)
#define PWR_BUS_LP_CTL0_PERI_AXI_AHB_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_AHB_LP_LMT_POS)
#define PWR_BUS_LP_CTL0_PERI_AXI_DMA_AXI_S1_LP_LMT_POS	(28)
#define PWR_BUS_LP_CTL0_PERI_AXI_DMA_AXI_S1_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL0_PERI_AXI_DMA_AXI_S1_LP_LMT_POS)

#define PWR_BUS_LP_CTL1_A7_PERI_AXI_LP_EN				(0x1UL << 0)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_EBUS_LP_EN			(0x1UL << 1)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_DBUS_LP_EN			(0x1UL << 2)
#define PWR_BUS_LP_CTL1_A7_PERI_AXI_LP_LMT_POS			(8)
#define PWR_BUS_LP_CTL1_A7_PERI_AXI_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL1_A7_PERI_AXI_LP_LMT_POS)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_EBUS_LP_LMT_POS	(12)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_EBUS_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL1_PERI_AXI_ON2_EBUS_LP_LMT_POS)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_DBUS_LP_LMT_POS	(16)
#define PWR_BUS_LP_CTL1_PERI_AXI_ON2_DBUS_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL1_PERI_AXI_ON2_DBUS_LP_LMT_POS)

#define PWR_BUS_LP_CTL2_DMA_AXI_DDR_AXI_M5_LP_EN		(0x1UL << 0)
#define PWR_BUS_LP_CTL2_DMA_AXI_PERI_AXI_M1_LP_EN		(0x1UL << 1)
#define PWR_BUS_LP_CTL2_DMA_AXI_ACP_MH2X_LP_EN			(0x1UL << 2)
#define PWR_BUS_LP_CTL2_DMA_AXI_AP_DMAG_ACP_LP_EN		(0x1UL << 3)
#define PWR_BUS_LP_CTL2_DMA_AXI_DMAG_DMA_LP_EN			(0x1UL << 4)
#define PWR_BUS_LP_CTL2_DMA_AXI_DDR_AXI_M5_LP_LMT_POS	(8)
#define PWR_BUS_LP_CTL2_DMA_AXI_DDR_AXI_M5_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL2_DMA_AXI_DDR_AXI_M5_LP_LMT_POS)
#define PWR_BUS_LP_CTL2_DMA_AXI_PERI_AXI_M1_LP_LMT_POS	(12)
#define PWR_BUS_LP_CTL2_DMA_AXI_PERI_AXI_M1_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL2_DMA_AXI_PERI_AXI_M1_LP_LMT_POS)
#define PWR_BUS_LP_CTL2_DMA_AXI_ACP_MH2X_LP_LMT_POS		(16)
#define PWR_BUS_LP_CTL2_DMA_AXI_ACP_MH2X_LP_LMT_MSK		(0xFUL << PWR_BUS_LP_CTL2_DMA_AXI_ACP_MH2X_LP_LMT_POS)
#define PWR_BUS_LP_CTL2_DMA_AXI_AP_DMAG_ACP_LP_LMT_POS	(20)
#define PWR_BUS_LP_CTL2_DMA_AXI_AP_DMAG_ACP_LP_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL2_DMA_AXI_AP_DMAG_ACP_LP_LMT_POS)
#define PWR_BUS_LP_CTL2_DMA_AXI_DMAG_DMA_LP_EN_LMT_POS	(24)
#define PWR_BUS_LP_CTL2_DMA_AXI_DMAG_DMA_LP_EN_LMT_MSK	(0xFUL << PWR_BUS_LP_CTL2_DMA_AXI_DMAG_DMA_LP_EN_LMT_POS)

#define PWR_BUS_LP_CTL3_A7_AXI_MAIN_LP_EN				(0x1UL << 0)
#define PWR_BUS_LP_CTL3_DMA_AXI_S0_LP_EN				(0x1UL << 1)
#define PWR_BUS_LP_CTL3_DMA_AXI_MAIN_LP_EN				(0x1UL << 2)
#define PWR_BUS_LP_CTL3_DMA_AXI_USB_LP_EN				(0x1UL << 3)
#define PWR_BUS_LP_CTL3_A7_AXI_MAIN_LP_LMT_POS			(8)
#define PWR_BUS_LP_CTL3_A7_AXI_MAIN_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL3_A7_AXI_MAIN_LP_LMT_POS)
#define PWR_BUS_LP_CTL3_DMA_AXI_S0_LP_LMT_POS			(12)
#define PWR_BUS_LP_CTL3_DMA_AXI_S0_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL3_DMA_AXI_S0_LP_LMT_POS)
#define PWR_BUS_LP_CTL3_DMA_AXI_MAIN_LP_LMT_POS			(16)
#define PWR_BUS_LP_CTL3_DMA_AXI_MAIN_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL3_DMA_AXI_MAIN_LP_LMT_POS)
#define PWR_BUS_LP_CTL3_DMA_AXI_USB_LP_LMT_POS			(20)
#define PWR_BUS_LP_CTL3_DMA_AXI_USB_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL3_DMA_AXI_USB_LP_LMT_POS)

#define PWR_BUS_LP_CTL4_DDR_AXI_MAIN_LP_EN				(0x1UL << 0)
#define PWR_BUS_LP_CTL4_DDR_AXI_ON2_D_LP_EN				(0x1UL << 3)
#define PWR_BUS_LP_CTL4_DDR_AXI_ISP_LP_EN				(0x1UL << 4)
#define PWR_BUS_LP_CTL4_DDR_AXI_MAIN_LP_LMT_POS			(8)
#define PWR_BUS_LP_CTL4_DDR_AXI_MAIN_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL4_DDR_AXI_MAIN_LP_LMT_POS)
#define PWR_BUS_LP_CTL4_DDR_AXI_ON2_D_LP_LMT_POS		(20)
#define PWR_BUS_LP_CTL4_DDR_AXI_ON2_D_LP_LMT_MSK		(0xFUL << PWR_BUS_LP_CTL4_DDR_AXI_ON2_D_LP_LMT_POS)
#define PWR_BUS_LP_CTL4_DDR_AXI_ISP_LP_LMT_POS			(24)
#define PWR_BUS_LP_CTL4_DDR_AXI_ISP_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL4_DDR_AXI_ISP_LP_LMT_POS)

#define PWR_DEVICE_ST_A7_WFI_POS						(0)
#define PWR_DEVICE_ST_A7_WFI_MSK						(0xFUL << PWR_DEVICE_ST_A7_WFI_POS)
#define PWR_DEVICE_ST_L2C_WFI							(0x1UL << 4)
#define PWR_DEVICE_ST_ADB_S_CACTIVE						(0x1UL << 5)
#define PWR_DEVICE_ST_ADB_M_CACTIVE						(0x1UL << 6)
#define PWR_DEVICE_ST_AP_DMAG_IDLE						(0x1UL << 8)

#define PWR_BUS_LP_CTL5_PERI_AXI_UAC_LP_EN				(0x1UL << 3)
#define PWR_BUS_LP_CTL5_PERI_AXI_UAC_LP_LMT_POS			(20)
#define PWR_BUS_LP_CTL5_PERI_AXI_UAC_LP_LMT_MSK			(0xFUL << PWR_BUS_LP_CTL5_PERI_AXI_UAC_LP_LMT_POS)


#define WOKOO_PWR_BASE									0xA0151000


#endif /* _WOKOO_PWR_H_ */

