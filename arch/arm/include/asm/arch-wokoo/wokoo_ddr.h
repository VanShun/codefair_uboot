/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_DDR_H_
#define _WOKOO_DDR_H_




struct wokoo_ddr_pwr {
	uint32_t reserved0;			/*!< Offset: 0x000  reserved Register */
	uint32_t PLLCNT;			/*!< Offset: 0x004  timing control register */
	uint32_t CTRL;				/*!< Offset: 0x008  DDR_PWR control register */
	uint32_t DIVCLKCTL;			/*!< Offset: 0x00C  DDR_PWR divided clock control register */
	uint32_t APBCLKCTL;			/*!< Offset: 0x010  COM_APB APB module clock control register */
	uint32_t DDRCLKCTL;			/*!< Offset: 0x014  MEMCTL module related clock control registers */
	uint32_t reserved1[5];		/*!< Offset: 0x018~0x028  reserved Register */
	uint32_t CLKOUT0_CTL;		/*!< Offset: 0x02C  CLKOUT0 clock control register */
	uint32_t PCLKEN;			/*!< Offset: 0x030  APB bus clock output enable control register */
	uint32_t CLKEN0;			/*!< Offset: 0x034  module working clock output enable control register */
	uint32_t RESET;				/*!< Offset: 0x038  reset control register */
	uint32_t MEMCTL_STATE;		/*!< Offset: 0x03C  MEMCTL module status register */
	uint32_t ADDRCTL_CS0;		/*!< Offset: 0x040  MEMCTL CS0 dddress mapping control register */
	uint32_t ADDRCTL_CS1;		/*!< Offset: 0x044  MEMCTL CS1 dddress mapping control register */
	uint32_t ADDRCTL;			/*!< Offset: 0x048  MEMCTL address signal conversion control register */
	uint32_t ADDRSEL0;			/*!< Offset: 0x04C  MEMCTL dddress signal conversion status register 0 */
	uint32_t ADDRSEL1;			/*!< Offset: 0x050  MEMCTL Address signal conversion status register 1 */
	uint32_t BWCALIDCTL0;		/*!< Offset: 0x054  MEMCTL bandwidth statistics ID control register 0 */
	uint32_t BWCALIDCTL1;		/*!< Offset: 0x058  MEMCTL bandwidth statistics ID control register 1 */
	uint32_t BWCALCNT0;			/*!< Offset: 0x05C  MEMCTL bandwidth statistics counter 0 */
	uint32_t BWCALCNT1;			/*!< Offset: 0x060  MEMCTL bandwidth statistics counter 1 */
	uint32_t BWCALCTL;			/*!< Offset: 0x064  MEMCTL bandwidth statistics control register */
	uint32_t reserved1_6;		/*!< Offset: 0x068  reserved Register */
	uint32_t BWCALNUM_A7;		/*!< Offset: 0x06C  MEMCTL bandwidth statistics result register£¨A9£© */
	uint32_t reserved1_7;		/*!< Offset: 0x070  reserved Register */
	uint32_t BWCALNUM_DDR_AXI;	/*!< Offset: 0x074  MEMCTL bandwidth statistics result register£¨DDR_AXI£© */
	uint32_t INTR_EN;			/*!< Offset: 0x078  DDR_PWR interrupt enable register */
	uint32_t reserved2;			/*!< Offset: 0x07C  reserved Register */
	uint32_t INTR_RAW;			/*!< Offset: 0x080  DDR_PWR interrupt raw status register */
	uint32_t INTR_ST;			/*!< Offset: 0x084  DDR_PWR interrupt status register */
	uint32_t INTR_CLR;			/*!< Offset: 0x088  DDR_PWR interrupt clear register */
	uint32_t reserved3[2];		/*!< Offset: 0x08C~0x090  reserved Register */
	uint32_t MEMCTL_DTOATOCTL;	/*!< Offset: 0x094  MEMCTL module test pin control register */
	uint32_t LPCTL;				/*!< Offset: 0x098  low power control register */
	uint32_t reserved5;			/*!< Offset: 0x09C  reserved Register */
	uint32_t GENERAL_REG_1;		/*!< Offset: 0x0A0  DDR_PWR general register 1 */
	uint32_t GENERAL_REG_2;		/*!< Offset: 0x0A4  DDR_PWR general register 2 */
	uint32_t GENERAL_REG_3;		/*!< Offset: 0x0A8  DDR_PWR general register 3 */
	uint32_t GENERAL_REG_4;		/*!< Offset: 0x0AC  DDR_PWR general register 4 */
	uint32_t reserved6[12];		/*!< Offset: 0x0B0~0x0DC  reserved Register */
	uint32_t GENERAL_REG_5;		/*!< Offset: 0x0E0  DDR_PWR general register 5 */
	uint32_t GENERAL_REG_6;		/*!< Offset: 0x0E4  DDR_PWR general register 6 */
	uint32_t GENERAL_REG_7;		/*!< Offset: 0x0E8  DDR_PWR general register 7 */
	uint32_t GENERAL_REG_8;		/*!< Offset: 0x0EC  DDR_PWR general register 8 */
	uint32_t MEMCTL_FREQ_ADJ;	/*!< Offset: 0x0F0  MEMCTL FM control register */
	uint32_t CLKEN1;			/*!< Offset: 0x0F4  module working clock enable register 1 */
	uint32_t MEMCTL_CTL;		/*!< Offset: 0x0F8  MEMCTL ontrol register */
	uint32_t BWCAL_CLKCTL;		/*!< Offset: 0x0FC  bandwidth statistics clock control register */
	uint32_t reserved7[4];		/*!< Offset: 0x100~0x10C  reserved Register */
	uint32_t BWCAL_DR_NUM1;		/*!< Offset: 0x110  MEMCTL bandwidth statistics read data times 1 */
	uint32_t BWCAL_DW_NUM1;		/*!< Offset: 0x114  MEMCTL bandwidth statistics write data times 1 */
	uint32_t BWCAL_IR_NUM1;		/*!< Offset: 0x118  MEMCTL candwidth statistics read instructions 1 */
	uint32_t reserved8;			/*!< Offset: 0x11C  reserved Register */
	uint32_t reserved9[4];		/*!< Offset: 0x120~0x12C  reserved Register */
	uint32_t BWCAL_DR_NUM3;		/*!< Offset: 0x130  MEMCTL bandwidth statistics read data times 3 */
	uint32_t BWCAL_DW_NUM3;		/*!< Offset: 0x134  MEMCTL bandwidth statistics write data times 3 */
	uint32_t BWCAL_IR_NUM3;		/*!< Offset: 0x138  MEMCTL bandwidth statistics read instructions 3 */
	uint32_t reserved10;		/*!< Offset: 0x13C  reserved Register */
	uint32_t TM_CTL;			/*!< Offset: 0x140  timer counter control register */
	uint32_t TM_INIT_VAL;		/*!< Offset: 0x144  timer counter initial value register */
	uint32_t TM_CUR_VAL;		/*!< Offset: 0x148  timer counter current value register */
	uint32_t A7EVENTI_SET;		/*!< Offset: 0x14C  A7 EVENTI control register */
	uint32_t AXI0_CLK_CTL;		/*!< Offset: 0x150  AXI0 clock control register */
	uint32_t AXI0_DF_CTL;		/*!< Offset: 0x154  AXI0 dynamic frequency control register */
	uint32_t reserved11[2];		/*!< Offset: 0x158~0x15C  reserved Register */
	uint32_t MEMCTL_LPCTL1;		/*!< Offset: 0x160  MEMCTL low power control register 1 */
	uint32_t MEMCTL_LPCTL2;		/*!< Offset: 0x164  MEMCTL low power control register 2 */
	uint32_t reserved12[3];		/*!< Offset: 0x168~0x170  reserved Register */
	uint32_t DDRRW_ID0;			/*!< Offset: 0x174  DDR access ID indicator register 0 */
	uint32_t DDRRW_ID1;			/*!< Offset: 0x178  DDR access ID indicator register 1 */
	uint32_t reserved13[7];		/*!< Offset: 0x17C~0x194  reserved Register */
	uint32_t APOSC_CTL;			/*!< Offset: 0x198  AP OSC control register */
	uint32_t SLPFSM_ST;			/*!< Offset: 0x19C  sleep state machine status register */
};

struct wokoo_ddr_ctrl {
	uint32_t MSTR;				/*!< Offset: 0x000  Master Register0 */
	uint32_t STAT;				/*!< Offset: 0x004  Operating Mode Status Register */
	uint32_t MSTR1;				/*!< Offset: 0x008  Master Register1 */
	uint32_t reserved0;			/*!< Offset: 0x00C  reserved Register*/
	uint32_t MRCTRL0;			/*!< Offset: 0x010  Mode Register Read/Write Control Register 0  */
	uint32_t MRCTRL1;			/*!< Offset: 0x014  Mode Register Read/Write Control Register 1   */
	uint32_t MRSTAT;			/*!< Offset: 0x018  Mode Register Read/Write Status Register  */
	uint32_t MRCTRL2;			/*!< Offset: 0x01C  Mode Register Read/Write Control Register 2 */
	uint32_t DERATEEN;			/*!< Offset: 0x020  Temperature Derate Enable Register  */
	uint32_t DERATEINT;			/*!< Offset: 0x024  Temperature Derate Interval Register */
	uint32_t MSTR2;				/*!< Offset: 0x028  Master Register2 */
	uint32_t reserved1;			/*!< Offset: 0x02C  reserved Register*/
	uint32_t PRWCTL;			/*!< Offset: 0x030  Low Power Control Register */
	uint32_t PWRTMG;			/*!< Offset: 0x034  Low Power Timing Register  */
	uint32_t HWLPCTL;			/*!< Offset: 0x038  Hardware Low Power Control Register */
	uint32_t HWFFCCTL;			/*!< Offset: 0x03C  Hardware Fast Frequency Change (HWFFC) Control Register */
	uint32_t HWFFCSTAT;			/*!< Offset: 0x040  Hardware Fast Frequency Change (HWFFC) Status Register */
	uint32_t reserved2[3];		/*!< Offset: 0x044~0x04C  reserved Register*/
	uint32_t RFSHCTL0;			/*!< Offset: 0x050  Refresh Control Register 0  */
	uint32_t RFSHCTL1;			/*!< Offset: 0x054  Refresh Control Register 1  */
	uint32_t RFSHCTL2;			/*!< Offset: 0x058  Refresh Control Register 2  */
	uint32_t RFSHCTL4;			/*!< Offset: 0x05C  Refresh Control Register 4 */
	uint32_t RFSHCTL3;			/*!< Offset: 0x060  Refresh Control Register 3 */
	uint32_t RFSHTMG;			/*!< Offset: 0x064  Refresh Timing Register */
	uint32_t RFSHTMG1;			/*!< Offset: 0x068  Refresh Timing Register1 */
	uint32_t reserved3;			/*!< Offset: 0x06C  reserved Register*/
	uint32_t ECCCFG0;			/*!< Offset: 0x070  ECC Configuration Register 0*/
	uint32_t ECCCFG1;			/*!< Offset: 0x074  ECC Configuration Register 1*/
	uint32_t ECCSTAT;			/*!< Offset: 0x078  SECDED ECC Status Register */
	uint32_t ECCCLR;			/*!< Offset: 0x07C  ECC Clear Register */
	uint32_t ECCERRCNT;			/*!< Offset: 0x080  ECC Error Counter Register */
	uint32_t ECCCADDR0;			/*!< Offset: 0x084  ECC Corrected Error Address Register 0*/
	uint32_t ECCCADDR1;			/*!< Offset: 0x088  ECC Corrected Error Address Register 1*/
	uint32_t ECCCSYN0;			/*!< Offset: 0x08C  ECC Corrected Syndrome Register 0 */
	uint32_t ECCCSYN1;			/*!< Offset: 0x090  ECC Corrected Syndrome Register 1 */
	uint32_t ECCCSYN2;			/*!< Offset: 0x094  ECC Corrected Syndrome Register 2 */
	uint32_t ECCBITMASK0;		/*!< Offset: 0x098  ECC Corrected Data Bit Mask Register 0 */
	uint32_t ECCBITMASK1;		/*!< Offset: 0x09C  ECC Corrected Data Bit Mask Register 1 */
	uint32_t ECCBITMASK2;		/*!< Offset: 0x0A0  ECC Corrected Data Bit Mask Register 2 */
	uint32_t ECCUADDR0;			/*!< Offset: 0x0A4  ECC Uncorrected Error Address Register 0 */
	uint32_t ECCUADDR1;			/*!< Offset: 0x0A8  ECC Uncorrected Error Address Register 1*/
	uint32_t ECCUSYN0;			/*!< Offset: 0x0AC  ECC Uncorrected Syndrome Register 0*/
	uint32_t ECCUSYN1;			/*!< Offset: 0x0B0  ECC Uncorrected Syndrome Register 1*/
	uint32_t ECCUSYN2;			/*!< Offset: 0x0B4  ECC Uncorrected Syndrome Register 2 */
	uint32_t ECCPOISONADDR0;	/*!< Offset: 0x0B8  ECC Data Poisoning Address Register 0*/
	uint32_t ECCPOISONADDR1;	/*!< Offset: 0x0BC  ECC Data Poisoning Address Register 1*/
	uint32_t CRCPARCTL0;		/*!< Offset: 0x0C0  CRC Parity Control Register0*/
	uint32_t CRCPARCTL1;		/*!< Offset: 0x0C4  CRC Parity Control Register1*/
	uint32_t CRCPARCTL2;		/*!< Offset: 0x0C8  CRC Parity Control Register2*/
	uint32_t CRCPARSTAT;		/*!< Offset: 0x0CC  CRC Parity Status Register*/
	uint32_t INIT0;				/*!< Offset: 0x0D0  SDRAM Initialization Register 0*/
	uint32_t INIT1;				/*!< Offset: 0x0D4  SDRAM Initialization Register 1*/
	uint32_t INIT2;				/*!< Offset: 0x0D8  SDRAM Initialization Register 2*/
	uint32_t INIT3;				/*!< Offset: 0x0DC  SDRAM Initialization Register 3*/
	uint32_t INIT4;				/*!< Offset: 0x0E0  SDRAM Initialization Register 4*/
	uint32_t INIT5;				/*!< Offset: 0x0E4  SDRAM Initialization Register 5*/
	uint32_t INIT6;				/*!< Offset: 0x0E8  SDRAM Initialization Register 6 */
	uint32_t INIT7;				/*!< Offset: 0x0EC  SDRAM Initialization Register 7 */
	uint32_t DIMMCTL;			/*!< Offset: 0x0F0  DIMM Control Register */
	uint32_t RANKCTL;			/*!< Offset: 0x0F4  Rank Control Register */
	uint32_t reserved4;			/*!< Offset: 0x0F8  Reserved Register */
	uint32_t CHCTL;				/*!< Offset: 0x0FC  Channel Control Register */
	uint32_t DRAMTMG0;			/*!< Offset: 0x100  SDRAM Timing Register 0*/
	uint32_t DRAMTMG1;			/*!< Offset: 0x104  SDRAM Timing Register 1*/
	uint32_t DRAMTMG2;			/*!< Offset: 0x108  SDRAM Timing Register 2*/
	uint32_t DRAMTMG3;			/*!< Offset: 0x10C  SDRAM Timing Register 3*/
	uint32_t DRAMTMG4;			/*!< Offset: 0x110  SDRAM Timing Register 4*/
	uint32_t DRAMTMG5;			/*!< Offset: 0x114  SDRAM Timing Register 5*/
	uint32_t DRAMTMG6;			/*!< Offset: 0x118  SDRAM Timing Register 6*/
	uint32_t DRAMTMG7;			/*!< Offset: 0x11C  SDRAM Timing Register 7*/
	uint32_t DRAMTMG8;			/*!< Offset: 0x120  SDRAM Timing Register 8*/
	uint32_t DRAMTMG9;			/*!< Offset: 0x124  SDRAM Timing Register 9*/
	uint32_t DRAMTMG10;			/*!< Offset: 0x128  SDRAM Timing Register 10*/
	uint32_t DRAMTMG11;			/*!< Offset: 0x12C  SDRAM Timing Register 11*/
	uint32_t DRAMTMG12;			/*!< Offset: 0x130  SDRAM Timing Register 12*/
	uint32_t DRAMTMG13;			/*!< Offset: 0x134  SDRAM Timing Register 13*/
	uint32_t DRAMTMG14;			/*!< Offset: 0x138  SDRAM Timing Register 14*/
	uint32_t DRAMTMG15;			/*!< Offset: 0x13C  SDRAM Timing Register 15*/
	uint32_t DRAMTMG16;			/*!< Offset: 0x140  SDRAM Timing Register 16 */
	uint32_t DRAMTMG17;			/*!< Offset: 0x144  SDRAM Timing Register 17*/
	uint32_t reserved5[10];		/*!< Offset: 0x148~16C  Reserved Register */
	uint32_t MRAMTMG0;			/*!< Offset: 0x170  MRAM Timing Register 0*/
	uint32_t MRAMTMG1;			/*!< Offset: 0x174  MRAM Timing Register 1*/
	uint32_t MRAMTMG4;			/*!< Offset: 0x178  MRAM Timing Register 4*/
	uint32_t MRAMTMG9;			/*!< Offset: 0x17C  MRAM Timing Register 9*/
	uint32_t ZQCTL0;			/*!< Offset: 0x180  ZQ Control Register 0*/
	uint32_t ZQCTL1;			/*!< Offset: 0x184  ZQ Control Register 1*/
	uint32_t ZQCTL2;			/*!< Offset: 0x188  ZQ Control Register 2*/
	uint32_t ZQSTAT;			/*!< Offset: 0x18C  ZQ Status Register*/
	uint32_t DFITMG0;			/*!< Offset: 0x190  DFI Timing Register 0*/
	uint32_t DFITMG1;			/*!< Offset: 0x194  DFI Timing Register 1*/
	uint32_t DFILPCFG0;			/*!< Offset: 0x198  DFI Low Power Configuration Register 0*/
	uint32_t DFILPCFG1;			/*!< Offset: 0x19C  DFI Low Power Configuration Register 1*/
	uint32_t DFIUPD0;			/*!< Offset: 0x1A0  DFI Update Register 0*/
	uint32_t DFIUPD1;			/*!< Offset: 0x1A4  DFI Update Register 1 */
	uint32_t DFIUPD2 ;			/*!< Offset: 0x1A8  DFI Update Register 2*/
	uint32_t reserved6;			/*!< Offset: 0x1AC  Reserved Register */
	uint32_t DFIMISC;			/*!< Offset: 0x1B0  DFI Miscellaneous Control Register*/
	uint32_t DFITMG2;			/*!< Offset: 0x1B4  DFI Timing Register 2*/
	uint32_t DFITMG3;			/*!< Offset: 0x1B8  DFI Timing Register 3*/
	uint32_t DFISTAT;			/*!< Offset: 0x1BC	DFI Status Register  */
	uint32_t DBICTL;			/*!< Offset: 0x1C0  DM/DBI Control Register */
	uint32_t DFIPHYMSTR;		/*!< Offset: 0x1C4  DFI PHY Master*/
	uint32_t reserved7[14];		/*!< Offset: 0x1C8~0x1FC  Reserved Register */
	uint32_t ADDRMAP0;			/*!< Offset: 0x200  Address Map Register 0*/
	uint32_t ADDRMAP1;			/*!< Offset: 0x204  Address Map Register 1*/
	uint32_t ADDRMAP2;			/*!< Offset: 0x208  Address Map Register 2*/
	uint32_t ADDRMAP3;			/*!< Offset: 0x20C  Address Map Register 3*/
	uint32_t ADDRMAP4;			/*!< Offset: 0x210  Address Map Register 4*/
	uint32_t ADDRMAP5;			/*!< Offset: 0x214  Address Map Register 5*/
	uint32_t ADDRMAP6;			/*!< Offset: 0x218  Address Map Register 6*/
	uint32_t ADDRMAP7;			/*!< Offset: 0x21C  Address Map Register 7*/
	uint32_t ADDRMAP8;			/*!< Offset: 0x220  Address Map Register 8*/
	uint32_t ADDRMAP9;			/*!< Offset: 0x224  Address Map Register 9*/
	uint32_t ADDRMAP10;			/*!< Offset: 0x228  Address Map Register 10*/
	uint32_t ADDRMAP11;			/*!< Offset: 0x22C  Address Map Register 11*/
	uint32_t reserved8[4];		/*!< Offset: 0x230~0x23C  Reserved Register*/
	uint32_t ODTCFG;			/*!< Offset: 0x240  ODT Configuration Register*/
	uint32_t ODTMAP;			/*!< Offset: 0x244  ODT/Rank Map Register*/
	uint32_t reserved9[2];		/*!< Offset: 0x248~0x24C  Reserved Register*/
	uint32_t SCHED;				/*!< Offset: 0x250  Scheduler Control Register*/
	uint32_t SCHED1;			/*!< Offset: 0x254  Scheduler Control Register 1*/
	uint32_t SCHED2;			/*!< Offset: 0x258  Scheduler Control Register 2*/
	uint32_t PERFHPR1;			/*!< Offset: 0x25C  High Priority Read CAM Register 1*/
	uint32_t reserved10;		/*!< Offset: 0x260  Reserved Register*/
	uint32_t PERFLPR1;			/*!< Offset: 0x264  Low Priority Read CAM Register 1*/
	uint32_t reserved11;		/*!< Offset: 0x268  Reserved Register*/
	uint32_t PERFWR1;			/*!< Offset: 0x26C  Write CAM Register 1*/
	uint32_t reserved12[4];		/*!< Offset: 0x270~0x27C  Reserved Register*/
	uint32_t DQMAP0;			/*!< Offset: 0x280  DQ Map Register 0*/
	uint32_t DQMAP1;			/*!< Offset: 0x284  DQ Map Register 1*/
	uint32_t DQMAP2;			/*!< Offset: 0x288  DQ Map Register 2 */
	uint32_t DQMAP3;			/*!< Offset: 0x28C  DQ Map Register 3*/
	uint32_t DQMAP4;			/*!< Offset: 0x290  DQ Map Register 4*/
	uint32_t DQMAP5;			/*!< Offset: 0x294  DQ Map Register 5*/
	uint32_t reserved13[26];	/*!< Offset: 0x298~0x2FC  Reserved Register*/
	uint32_t DBG0;				/*!< Offset: 0x300  Debug Register 0*/
	uint32_t DBG1;				/*!< Offset: 0x304  Debug Register 1*/
	uint32_t DBGCAM;			/*!< Offset: 0x308  CAM Debug Register*/
	uint32_t DBGCMD;			/*!< Offset: 0x30C  Command Debug Register*/
	uint32_t DBGSTAT;			/*!< Offset: 0x310  Status Debug Register*/
	uint32_t reserved14[3];		/*!< Offset: 0x314~0x31C  Reserved Register*/
	uint32_t SWCTL;				/*!< Offset: 0x320  Software Register Programming Control Enable*/
	uint32_t SWSTAT;			/*!< Offset: 0x324  Software Register Programming Control Status*/
	uint32_t reserved15[2];		/*!< Offset: 0x328~0x32C  Reserved Register*/
	uint32_t OCPARCFG0;			/*!< Offset: 0x330  On-Chip Parity Configuration Register 0*/
	uint32_t OCPARCFG1;			/*!< Offset: 0x334  On-Chip Parity Configuration Register 1*/
	uint32_t OCPARCFG2;			/*!< Offset: 0x338  On-Chip Parity Configuration Register 2*/
	uint32_t OCPARCFG3;			/*!< Offset: 0x33C  On-Chip Parity Configuration Register 3*/
	uint32_t OCPARSTAT0;		/*!< Offset: 0x340  On-Chip Parity Status Register 0*/
	uint32_t OCPARSTAT1;		/*!< Offset: 0x344  On-Chip Parity Status Register 1*/
	uint32_t OCPARWLOG0;		/*!< Offset: 0x348  On-Chip Parity Write Data Log Register 0*/
	uint32_t OCPARWLOG1;		/*!< Offset: 0x34C  On-Chip Parity Write Data Log Register 1*/
	uint32_t OCPARWLOG2;		/*!< Offset: 0x350  On-Chip Parity Write Data Log Register 2*/
	uint32_t OCPARAWLOG0;		/*!< Offset: 0x354  On-Chip Parity Write Address Log Register 0*/
	uint32_t OCPARAWLOG1;		/*!< Offset: 0x358  On-Chip Parity Write Address Log Register 1*/
	uint32_t OCPARRLOG0;		/*!< Offset: 0x35C  On-Chip Parity Read Data Log Register 0*/
	uint32_t OCPARRLOG1;		/*!< Offset: 0x360  On-Chip Parity Read Data Log Register 1*/
	uint32_t OCPARARLOG0;		/*!< Offset: 0x364  On-Chip Parity Read Address Log Register 0*/
	uint32_t OCPARARLOG1;		/*!< Offset: 0x368  On-Chip Parity Read Address Log Register 1*/
	uint32_t POISONCFG;			/*!< Offset: 0x36C  AXI Poison Configuration Register. Common for all AXI ports*/
	uint32_t POISONSTAT;		/*!< Offset: 0x370  AXI Poison Status Register*/
	uint32_t ADVECCINDEX;		/*!< Offset: 0x374  Advanced ECC Index Register*/
	uint32_t ADVECCSTAT;		/*!< Offset: 0x378  Advanced ECC Status Register*/
	uint32_t ECCPOISONPAT0;		/*!< Offset: 0x37C  ECC Poison Pattern 0 Register*/
	uint32_t ECCPOISONPAT1;		/*!< Offset: 0x380  ECC Poison Pattern 1 Register*/
	uint32_t ECCPOISONPAT2;		/*!< Offset: 0x384  ECC Poison Pattern 2 Register*/
	uint32_t ECCAPSTAT;			/*!< Offset: 0x388  Address protection within ECC Status Register*/
	uint32_t reserved16[5];		/*!< Offset: 0x38C~0x39C  Reserved Register*/

	uint32_t CAPARPOISONCTL;	/*!< Offset: 0x3A0  CA parity poison contrl Register*/
	uint32_t CAPARPOISONSTAT;	/*!< Offset: 0x3A4  CA parity poison status Register*/
	uint32_t reserved17[2];		/*!< Offset: 0x3A8~0x3AC  Reserved Register*/
	uint32_t DYNBSMSTAT;		/*!< Offset: 0x3B0  Dynamic BSM Status Register*/
	uint32_t reserved18[3];		/*!< Offset: 0x3B4~0x3BC  Reserved Register*/
	uint32_t REGPARCFG;			/*!< Offset: 0x3C0  Register Parity Configuration Register*/
	uint32_t REGPARSTAT;		/*!< Offset: 0x3C4  Register Parity Status Register*/
	uint32_t reserved19[2];		/*!< Offset: 0x3C8~0x3CC  Reserved Register*/
	uint32_t RCDINIT1;			/*!< Offset: 0x3D0  Control Word setting Register RCDINIT1*/
	uint32_t RCDINIT2;			/*!< Offset: 0x3D4  Control Word setting Register RCDINIT2*/
	uint32_t RCDINIT3;			/*!< Offset: 0x3D8  Control Word setting Register RCDINIT3*/
	uint32_t RCDINIT4;			/*!< Offset: 0x3DC  Control Word setting Register RCDINIT4*/
	uint32_t OCCAPCFG;			/*!< Offset: 0x3E0  On-Chip command/Address Protection Configuration Register*/
	uint32_t OCCAPSTAT;			/*!< Offset: 0x3E4  On-Chip command/Address Protection Status Register*/
	uint32_t OCCAPCFG1;			/*!< Offset: 0x3E8  On-Chip command/Address Protection Configuration Register 1*/
	uint32_t OCCAPSTAT1;		/*!< Offset: 0x3EC  On-Chip command/Address Protection Status Register 1*/
	uint32_t reserved20[3];		/*!< Offset: 0x3F0~0x3F8  Reserved Register*/
	uint32_t PSTAT;				/*!< Offset: 0x3FC  Port Status Register*/
	uint32_t PCCFG;				/*!< Offset: 0x400  Port Common Configuration Register*/
	uint32_t PCFGR_0;			/*!< Offset: 0x404  Port 0 Configuration Read Register*/
	uint32_t PCFGW_0;			/*!< Offset: 0x408  Port 0 Configuration Write Register*/
	uint32_t PCFGC_0;			/*!< Offset: 0x40C  Port 0 Common Configuration Register*/
    uint32_t reserved21[32];	/*!< Offset: 0x410~0x48C  Reserved Register*/
	uint32_t PCTRL_0;			/*!< Offset: 0x490  Port 0 Control Register*/
	uint32_t reserved22[8];		/*!< Offset: 0x494~0x4B0  Reserved Register*/
    uint32_t PCFGR_1;			/*!< Offset: 0x4B4 Port 1 Configuration Read Register*/
    uint32_t PCFGW_1;			/*!< Offset: 0x4B8  Port 1 Configuration Write Register*/
	uint32_t PCFGC_1;			/*!< Offset: 0x4BC  Port 1 Common Configuration Register*/
	uint32_t reserved23[32];	/*!< Offset: 0x4C0~0x53C  Reserved Register*/
	uint32_t PCTRL_1;			/*!< Offset: 0x540  Port 1 Control Register*/
	uint32_t reserved24[43];	/*!< Offset: 0x544~0x5EC  Reserved Register*/
	uint32_t PCTRL_2;			/*!< Offset: 0x5F0  Port 2 Control Register*/
};

struct wokoo_ddr_phy {
	uint32_t RIDR;				/*!< Offset: 0x000  Revision Identification Register */
	uint32_t PIR;				/*!< Offset: 0x004  PHY Initialization Register*/
	uint32_t PGCR;				/*!< Offset: 0x008  PHY General Configuration Register*/
	uint32_t PGSR;				/*!< Offset: 0x00C  PHY General Status Register*/
	uint32_t DLLGCR;			/*!< Offset: 0x010  DLL General Control Register*/
	uint32_t ACDLLCR;			/*!< Offset: 0x014  AC DLL Control Register*/
	uint32_t PTR0;				/*!< Offset: 0x018  PHY Timing Register 0*/
	uint32_t PTR1;				/*!< Offset: 0x01C  PHY Timing Register 1*/
	uint32_t PTR2;				/*!< Offset: 0x020  PHY Timing Register 2*/
	uint32_t ACIOCR;			/*!< Offset: 0x024  AC I/O Configuration Register*/
	uint32_t DXCCR;				/*!< Offset: 0x028  DATX8 Common Configuration Register*/
	uint32_t DSGCR;				/*!< Offset: 0x02C  DDR System General Configuration Register*/
	uint32_t DCR;				/*!< Offset: 0x030  DRAM Configuration Register*/
	uint32_t DTPR0;				/*!< Offset: 0x034  DRAM Timing Parameters Register 0 */
	uint32_t DTPR1;				/*!< Offset: 0x038  DRAM Timing Parameters Register 1 */
	uint32_t DTPR2;				/*!< Offset: 0x03C  DRAM Timing Parameters Register 2 */
	uint32_t MR0;				/*!< Offset: 0x040  Mode Register 0*/
	uint32_t MR1;				/*!< Offset: 0x044  Mode Register 1*/
	uint32_t MR2;				/*!< Offset: 0x048  Mode Register 2*/
	uint32_t MR3;				/*!< Offset: 0x04C  Mode Register 3*/
	uint32_t ODTCR;				/*!< Offset: 0x050  ODT Configuration Register */
	uint32_t DTAR;				/*!< Offset: 0x054  Data Training Address Register*/
	uint32_t DTDR0;				/*!< Offset: 0x058  Data Training Data Register 0*/
	uint32_t DTDR1;				/*!< Offset: 0x05C  Data Training Data Register 1*/
	uint32_t reserved0[24];		/*!< Offset: 0x060~0x0BC Reserved Register  */
	uint32_t DCUAR;				/*!< Offset: 0x0C0  DCU Address Register */
	uint32_t DCUDR;				/*!< Offset: 0x0C4  DCU Data Register*/
	uint32_t DCURR;				/*!< Offset: 0x0C8  DCU Run Register */
	uint32_t DCULR;				/*!< Offset: 0x0CC  DCU Loop Register */
	uint32_t DCUGCR;			/*!< Offset: 0x0D0  DCU General Configuration Register */
	uint32_t DCUTPR;			/*!< Offset: 0x0D4  DCU Timing Parameters Registers */
	uint32_t DCUSR0;			/*!< Offset: 0x0D8  DCU Status Register 0 */
	uint32_t DCUSR1;			/*!< Offset: 0x0DC  DCU Status Register 1 */
	uint32_t reserved1[8];		/*!< Offset: 0x0E0~0xFC Reserved Register  */
	uint32_t BISTRR;			/*!< Offset: 0x100  BIST Run Register */
	uint32_t BISTMSKR0;			/*!< Offset: 0x104  BIST Mask Register 0  */
	uint32_t BISTMSKR1;			/*!< Offset: 0x108  BIST Mask Register 1 */
	uint32_t BISTWCR;			/*!< Offset: 0x10C  BIST Word Count Register */
	uint32_t BISTLSR;			/*!< Offset: 0x110  BIST LFSR Seed Register */
	uint32_t BISTAR0;			/*!< Offset: 0x114  BIST Address Register 0 */
	uint32_t BISTAR1;			/*!< Offset: 0x118  BIST Address Register 1 */
	uint32_t BISTAR2;			/*!< Offset: 0x11C  BIST Address Register 2 */
	uint32_t BISTUDPR;			/*!< Offset: 0x120  BIST User Data Pattern Register */
	uint32_t BISTGSR;			/*!< Offset: 0x124  BIST General Status Register */
	uint32_t BISTWER;			/*!< Offset: 0x128  BIST Word Error Register */
	uint32_t BISTBER0;			/*!< Offset: 0x12C  BIST Bit Error Register 0 */
	uint32_t BISTBER1;			/*!< Offset: 0x130  BIST Bit Error Register 1 */
	uint32_t BISTBER2;			/*!< Offset: 0x134  BIST Bit Error Register 2 */
	uint32_t BISTWCSR;			/*!< Offset: 0x138  BIST Word Count Status Register */
	uint32_t BISTFWR0;			/*!< Offset: 0x13C  BIST Fail Word Register 0 */
	uint32_t BISTFWR1;			/*!< Offset: 0x140  BIST Fail Word Register 1 */
};


#define WOKOO_DDR_PWR_BASE		0xA0155000
#define WOKOO_DDR_CTL_BASE		0xA0152000
#define WOKOO_DDR_PHY_BASE		0xA0154000

void ddr_init(void);
void ddr3_init(void);


#endif /* _WOKOO_DDR_H_ */

