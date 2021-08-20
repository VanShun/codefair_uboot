
/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <linux/types.h>
#include <asm/io.h>
#include <asm/types.h>
#include <wait_bit.h>
#include <asm/arch-wokoo/wokoo_ddr.h>




/* DDR base addr */
static struct wokoo_ddr_pwr  *wokoo_ddr3_pwr  = (struct wokoo_ddr_pwr *)WOKOO_DDR_PWR_BASE;
static struct wokoo_ddr_ctrl *wokoo_ddr3_ctrl = (struct wokoo_ddr_ctrl *)WOKOO_DDR_CTL_BASE;
static struct wokoo_ddr_phy  *wokoo_ddr3_phy  = (struct wokoo_ddr_phy *)WOKOO_DDR_PHY_BASE;




/*
 *  ddr_PwrConfig - DDR PWR config
 *
 */
static void ddr3_PwrConfig(void)
{
	unsigned int data = 0;

	data = readl(&wokoo_ddr3_pwr->PCLKEN) | 0x30003;
	writel(data, &wokoo_ddr3_pwr->PCLKEN);//0x030

	data = readl(&wokoo_ddr3_pwr->CLKEN0) | 0x0c030c03;
	writel(data, &wokoo_ddr3_pwr->CLKEN0); //0x034

	data = (readl(&wokoo_ddr3_pwr->ADDRCTL_CS0) | 0x000a030e) & 0xfffaffff;
	writel(data, &wokoo_ddr3_pwr->ADDRCTL_CS0);//0x040

	data = (readl(&wokoo_ddr3_pwr->ADDRCTL_CS1) | 0x000a030e) & 0xfffaffff;
	writel(data, &wokoo_ddr3_pwr->ADDRCTL_CS1);//0x044
}

/*
 *  ddr_PhyInitConfig - DDR PHY config
 *
 */
static void ddr3_PhyInitConfig(void)
{
	unsigned int data = 0;

	data = readl(&wokoo_ddr3_phy->PGCR);
	writel(0x018c2e02, &wokoo_ddr3_phy->PGCR); //0x008

	data = readl(&wokoo_ddr3_phy->DCR);
	//writel(0x004, &wokoo_ddr3_phy->DCR);//lsh 0x030
    writel(0x003, &wokoo_ddr3_phy->DCR);//lsh
	data = readl(&wokoo_ddr3_phy->DXCCR);
	writel(0xc40, &wokoo_ddr3_phy->DXCCR);//0x028

	data = readl(&wokoo_ddr3_phy->MR0);
	//writel(0x421, &wokoo_ddr3_phy->MR0); //lsh 0x040
    writel(0x1521, &wokoo_ddr3_phy->MR0); //lsh 0x040
	data = readl(&wokoo_ddr3_phy->MR1);
	//writel(0xc3, &wokoo_ddr3_phy->MR1); //lsh 0x044
    writel(0004, &wokoo_ddr3_phy->MR1); //lsh 0x044
	data = readl(&wokoo_ddr3_phy->MR2);
	//writel(0x4, &wokoo_ddr3_phy->MR2);//lsh 0x048
     writel(0x0400, &wokoo_ddr3_phy->MR2);//lsh 0x048
	data = readl(&wokoo_ddr3_phy->MR3);
	//writel(0x2, &wokoo_ddr3_phy->MR3); //lsh 0x04C
    writel(0, &wokoo_ddr3_phy->MR3); //lsh 0x04C
	data = readl(&wokoo_ddr3_phy->DSGCR);
	//writel(0xf800025f, &wokoo_ddr3_phy->DSGCR);//lsh 0x02C
    writel(0xfa00025f, &wokoo_ddr3_phy->DSGCR);//lsh 0x02C
	data = readl(&wokoo_ddr3_phy->DTPR0);
	writel(0x409182ae, &wokoo_ddr3_phy->DTPR0);//0x034

	data = readl(&wokoo_ddr3_phy->DTPR1);
	writel(0x093300a0, &wokoo_ddr3_phy->DTPR1);//0x038

	data = readl(&wokoo_ddr3_phy->DTPR2);
	writel(0x10018c38, &wokoo_ddr3_phy->DTPR2);//0x03C
	
	data = data;
}

/*
 *  ddr_PhyInitMoniter - DDR PHY init moniter
 *
 */
static void ddr3_PhyInitMoniter(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	data = readl(&wokoo_ddr3_phy->PTR0);
	writel(0x0020a688, &wokoo_ddr3_phy->PTR0); //0x018
	writel(0x014130b4, &wokoo_ddr3_phy->PTR1); //0x01C
	writel(0x030e10c3, &wokoo_ddr3_phy->PTR2);//0x020

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr3_phy->PGSR);

		if ((data & 0x1) == 0x1)
		{
			loop = 0;
		}
	}
}

/*
 *  ddr_PhyInitStart - DDR PHY init start
 *
 */
static void ddr3_PhyInitStart(void)
{
	//writel(0x00040001, &wokoo_ddr3_phy->PIR);//lsh
	writel(0x000401e1, &wokoo_ddr3_phy->PIR);//lsh 0x004
}

/*
 *  ddr_PhyInitDone - DDR PHY init done
 *
 */
static void ddr3_PhyInitDone(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr3_phy->PGSR);
		if ((data & 0xf) == 0xf)
		{
			loop = 0;
		}
	}
}

/*
 *  ddr_DFIInitDone - DDR DFI init done
 *
 */
static void ddr3_DFIInitDone(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr3_ctrl->DFISTAT);
		if ((data & 0x1) == 0x1)
		{
			loop = 0;
		}
	}
}

/*
 *  ddr_waitSTATnormal - DDR wait status normal
 *
 */
static void ddr3_waitSTATnormal(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr3_ctrl->STAT);
		if ((data & 0xf) == 0x1)
		{
			loop = 0;
		}
	}
}

/*
 *  ddr_waitSWSTAT - DDR wait status
 *
 */
static void ddr3_waitSWSTAT(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr3_ctrl->SWSTAT);
		if ((data & 0x1) == 0x1)
		{
			loop = 0;
		}
	}
}

/*
 *  ddr_init - DDR init
 *
 */
void ddr3_init(void)
{
	
	//ddr_PwrConfig();
	/* DDR reset */
	writel(readl(&wokoo_ddr3_pwr->RESET) | 0x3000300, &wokoo_ddr3_pwr->RESET);
	printf("DDR3 init start\n");
	udelay(1000);
	writel((readl(&wokoo_ddr3_pwr->RESET) | 0x3000000) & 0XFFFFFCFF, &wokoo_ddr3_pwr->RESET);

	udelay(1000);
   ///  writel(readl(&wokoo_ddr3_pwr->RESET) | 0x3000300, &wokoo_ddr3_pwr->RESET);

	ddr3_PwrConfig();
	

	writel(0x02000200, &wokoo_ddr3_pwr->RESET); //0x038
	writel(0x00000000, &wokoo_ddr3_ctrl->SWCTL);//0x320

	writel(0x00000001, &wokoo_ddr3_ctrl->DBG1); //0x304
	writel(0x00000001, &wokoo_ddr3_ctrl->PRWCTL);//0x030

	/* LPDDR2|BURST_LEN_8|1 RANK 0x01040004 */
	//writel(0x00040004, &wokoo_ddr3_ctrl->MSTR); //lsh 0x000
	  writel(0x00040001, &wokoo_ddr3_ctrl->MSTR); //lsh
	/* MRCTRL0|RANK 0|mrw 0x80000010;0x00000030 */
	//writel(0x00000010, &wokoo_ddr3_ctrl->MRCTRL0);//lsh
     writel(0x0000a010, &wokoo_ddr3_ctrl->MRCTRL0);//lsh 0x010
	/* MR63 addr = 3F(or F3?) --by hhc (MRCTRL1) */
	//writel(0x00003f01, &wokoo_ddr3_ctrl->MRCTRL1);//lsh 0x014
	writel(0x00004f75, &wokoo_ddr3_ctrl->MRCTRL1);//lsh 0x014
	/* LPDDR2 derating disable */
	//writel(0x00000000, &wokoo_ddr3_ctrl->DERATEEN);//lsh 0x020
	writel(0x00000002, &wokoo_ddr3_ctrl->DERATEEN);//lsh 0x020
	/* LPDDR2 MR4 read interval */
	//writel(0xf829b026, &wokoo_ddr3_ctrl->DERATEINT);//lsh 0x024
	writel(0xa3c063cb, &wokoo_ddr3_ctrl->DERATEINT);//lsh 0x024
	/* LPDDR2 low power 0c00000002 powerdown_en */
	//writel(0x00000000, &wokoo_ddr3_ctrl->PRWCTL);//lsh 0x030
    writel(0x00000003, &wokoo_ddr3_ctrl->PRWCTL);//lsh 0x030
	/* LPDDR2 low power timing */
	writel(0x0040d904, &wokoo_ddr3_ctrl->PWRTMG);//0x034
	writel(0x00400010, &wokoo_ddr3_ctrl->PWRTMG);//0x034

	writel(0x004b0002, &wokoo_ddr3_ctrl->HWLPCTL); //0x038
	writel(0x00210000, &wokoo_ddr3_ctrl->RFSHCTL0);//0x050
	//writel(0x00000001, &wokoo_ddr3_ctrl->RFSHCTL3);//lsh 0x060
	writel(0x00000000, &wokoo_ddr3_ctrl->RFSHCTL3);//lsh 0x060
#if 0
	writel(0x00c30024, &wokoo_ddr3_ctrl->RFSHTMG);

	writel(0x00000010, &wokoo_ddr3_ctrl->ECCCFG0);
	writel(0x00000000, &wokoo_ddr3_ctrl->ECCCFG1);
	writel(0x00000000, &wokoo_ddr3_ctrl->ECCCLR);
	writel(0x000000a0, &wokoo_ddr3_ctrl->ECCPOISONADDR0);
	writel(0x01000d8a, &wokoo_ddr3_ctrl->ECCPOISONADDR1);
	writel(0x00000000, &wokoo_ddr3_ctrl->CRCPARCTL0);
#endif
	//writel(0x00020002, &wokoo_ddr3_ctrl->INIT0); //lsh 0x0D0
	writel(0x000200d2, &wokoo_ddr3_ctrl->INIT0); //lsh 0x0D0
	//writel(0x00010002, &wokoo_ddr3_ctrl->INIT1);//lsh 0x0D4
	writel(0x00600002, &wokoo_ddr3_ctrl->INIT1);//lsh 0x0D4
	//writel(0x00000e06, &wokoo_ddr3_ctrl->INIT2);//lsh 0x0D8
	//writel(0x00430004, &wokoo_ddr3_ctrl->INIT3);//lsh 0x0DC
	writel(0x15210005, &wokoo_ddr3_ctrl->INIT3);//lsh 0x0DC
	//writel(0x00020000, &wokoo_ddr3_ctrl->INIT4);//lsh 0x0E0
	writel(0x04400000, &wokoo_ddr3_ctrl->INIT4);//lsh 0x0E0
	#if 0
	//writel(0x00020000, &wokoo_ddr3_ctrl->INIT4);//lsh 0x0E0
	writel(0x00570000, &wokoo_ddr3_ctrl->INIT4);//lsh 0x0E0
	//writel(0x000e0005, &wokoo_ddr3_ctrl->INIT5);//lsh 0x0E4
     writel(0x00110314, &wokoo_ddr3_ctrl->INIT5);//lsh 0x0E4
	//writel(0x00000000, &wokoo_ddr3_ctrl->DIMMCTL);//lsh 0x0F0
     writel(0x00000001, &wokoo_ddr3_ctrl->DIMMCTL);//lsh 0x0F0
	 #endif
	 //writel(0x04000000, &wokoo_ddr3_ctrl->INIT4);//lsh 0x0E0
	 writel(0x00100314, &wokoo_ddr3_ctrl->INIT5);//lsh 0x0E4
	 writel(0x00000001, &wokoo_ddr3_ctrl->DIMMCTL);//lsh 0x0F0
	 
	 #if 0 //lsh
	/* LPDDR2 sdram timing regX */
	writel(0x0e141a04, &wokoo_ddr3_ctrl->DRAMTMG0);//0x100
	writel(0x00030206, &wokoo_ddr3_ctrl->DRAMTMG1);//0x104
	writel(0x03021b1b, &wokoo_ddr3_ctrl->DRAMTMG2);//0x108
	writel(0x0050100c, &wokoo_ddr3_ctrl->DRAMTMG3);//0x10C
	writel(0x08010408, &wokoo_ddr3_ctrl->DRAMTMG4);//0x110
	writel(0x02020606, &wokoo_ddr3_ctrl->DRAMTMG5);//0x114
	writel(0x02020005, &wokoo_ddr3_ctrl->DRAMTMG6);//0x118
	writel(0x00000202, &wokoo_ddr3_ctrl->DRAMTMG7);//0x11C
	writel(0x00000101, &wokoo_ddr3_ctrl->DRAMTMG8);//0x120
	writel(0x00000028, &wokoo_ddr3_ctrl->DRAMTMG14);//0x138
	writel(0x00000000, &wokoo_ddr3_ctrl->DRAMTMG15);//0x13C
#else
	writel(0x0e141a04, &wokoo_ddr3_ctrl->DRAMTMG0);//0x100
	writel(0x00030206, &wokoo_ddr3_ctrl->DRAMTMG1);//0x104
	writel(0x03021b1b, &wokoo_ddr3_ctrl->DRAMTMG2);//0x108
	writel(0x0050700c, &wokoo_ddr3_ctrl->DRAMTMG3);//0x10C
	writel(0x0a040405, &wokoo_ddr3_ctrl->DRAMTMG4);//0x110
	writel(0x05050403, &wokoo_ddr3_ctrl->DRAMTMG5);//0x114
	writel(0x00000000, &wokoo_ddr3_ctrl->DRAMTMG6);//0x118
	writel(0x00000505, &wokoo_ddr3_ctrl->DRAMTMG7);//0x11C
	writel(0x00001230, &wokoo_ddr3_ctrl->DRAMTMG8);//0x120
	//writel(0x00000028, &wokoo_ddr3_ctrl->DRAMTMG14);//0x138
	//writel(0x00000000, &wokoo_ddr3_ctrl->DRAMTMG15);//0x13C
#endif

	writel(0x40900024, &wokoo_ddr3_ctrl->ZQCTL0);//0x180
	writel(0x014abfd4, &wokoo_ddr3_ctrl->ZQCTL1);//0x184
	writel(0x00000000, &wokoo_ddr3_ctrl->ZQCTL2);//0x188
	
	//writel(0x02050103, &wokoo_ddr3_ctrl->DFITMG0);//lsh 0x190
	writel(0x02050104, &wokoo_ddr3_ctrl->DFITMG0);//lsh 0x190
	writel(0x00030202, &wokoo_ddr3_ctrl->DFITMG1);//0x194
	writel(0x07117101, &wokoo_ddr3_ctrl->DFILPCFG0);//0x198
	writel(0x80280005, &wokoo_ddr3_ctrl->DFIUPD0);//0x1A0
	writel(0x00a70026, &wokoo_ddr3_ctrl->DFIUPD1);//0x1A4
	writel(0x00000000, &wokoo_ddr3_ctrl->DFIUPD2);//0x1A8
	writel(0x00000031, &wokoo_ddr3_ctrl->DFIMISC);//0x1B0
	writel(0x00000000, &wokoo_ddr3_ctrl->DFIPHYMSTR);//0x1C4

	/* LPDDR2 addr map reg1 bank 31 */
	//writel(0x001f1f1f, &wokoo_ddr3_ctrl->ADDRMAP0);
	#if 0
	writel(readl( &wokoo_ddr3_ctrl->ADDRMAP1)|0x003f0707, &wokoo_ddr3_ctrl->ADDRMAP1);//0x204
	/* LPDDR2 addr map reg2 col */
	writel(0x00000000, &wokoo_ddr3_ctrl->ADDRMAP2);//0x208
	/* LPDDR2 addr map reg3 col */
	writel(0x1f000000, &wokoo_ddr3_ctrl->ADDRMAP3);//0x20C
	/* LPDDR2 addr map reg4 col */
	writel(0x00001f1f, &wokoo_ddr3_ctrl->ADDRMAP4);//0x210
	/* LPDDR2 addr map reg5 row */
	writel(0x05050505, &wokoo_ddr3_ctrl->ADDRMAP5);//0x214
	/* LPDDR2 addr map reg6 row */
	writel(0x0f0f0f05, &wokoo_ddr3_ctrl->ADDRMAP6);//0x218
	writel(0x001f1f05, &wokoo_ddr3_ctrl->ADDRMAP11);//0x22C

	/* LPDDR2 ODT config reg */
	writel(0x06010710, &wokoo_ddr3_ctrl->ODTCFG);//0x240
	/* LPDDR2 ODT/rank map reg */
	writel(0x00000000, &wokoo_ddr3_ctrl->ODTMAP);//0x244
	/* LPDDR2 scheduler control reg */
	writel(0x03080805, &wokoo_ddr3_ctrl->SCHED);//0x250
	writel(0x00000000, &wokoo_ddr3_ctrl->SCHED1);//0x254
	writel(0x0f000001, &wokoo_ddr3_ctrl->PERFHPR1);//0x25C
	writel(0x0f00007f, &wokoo_ddr3_ctrl->PERFLPR1);//0x264
	writel(0x0f00007f, &wokoo_ddr3_ctrl->PERFWR1);//0x26C
	#else
	writel(0x00080808, &wokoo_ddr3_ctrl->ADDRMAP1);//0x204
	/* LPDDR2 addr map reg2 col */
	writel(0x00000000, &wokoo_ddr3_ctrl->ADDRMAP2);//0x208
	/* LPDDR2 addr map reg3 col */
	writel(0x00000000, &wokoo_ddr3_ctrl->ADDRMAP3);//0x20C
	/* LPDDR2 addr map reg4 col */
	writel(0x00000000, &wokoo_ddr3_ctrl->ADDRMAP4);//0x210
	/* LPDDR2 addr map reg5 row */
	writel(0x07070707, &wokoo_ddr3_ctrl->ADDRMAP5);//0x214
	/* LPDDR2 addr map reg6 row */
	writel(0x07070707, &wokoo_ddr3_ctrl->ADDRMAP6);//0x218
	//writel(0x001f1f05, &wokoo_ddr3_ctrl->ADDRMAP11);//0x22C

	/* LPDDR2 ODT config reg */
	writel(0x06000604, &wokoo_ddr3_ctrl->ODTCFG);//0x240
	/* LPDDR2 ODT/rank map reg */
	writel(0x00000011, &wokoo_ddr3_ctrl->ODTMAP);//0x244
	/* LPDDR2 scheduler control reg */
	writel(0x03e90205, &wokoo_ddr3_ctrl->SCHED);//0x250
	writel(0x00000000, &wokoo_ddr3_ctrl->SCHED1);//0x254
	writel(0x0f000001, &wokoo_ddr3_ctrl->PERFHPR1);//0x25C
	writel(0x0f00007f, &wokoo_ddr3_ctrl->PERFLPR1);//0x264
	writel(0x0f00007f, &wokoo_ddr3_ctrl->PERFWR1);//0x26C
#endif
#if 0
	writel(0x00000011, &wokoo_ddr3_ctrl->DBG0);
	writel(0x00000000, &wokoo_ddr3_ctrl->DBG1);
	writel(0x00000000, &wokoo_ddr3_ctrl->DBGCMD);
	writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);
	writel(0x00010010, &wokoo_ddr3_ctrl->POISONCFG);
	#endif
	//writel(0x00000000, &wokoo_ddr3_ctrl->ADVECCINDEX);
	//writel(0x00000000, &wokoo_ddr3_ctrl->ECCPOISONPAT0);
	//writel(0x00000000, &wokoo_ddr3_ctrl->ECCPOISONPAT2);


#if 0
	/* PCCFG/port common cfg reg */
	writel(0x00000000, &wokoo_ddr3_ctrl->PCCFG);//0x400
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGR_0);//0x404
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGR_1);//0x4B4
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGW_0);//0x408
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGW_1);//0x4B8
	writel(0x00000001, &wokoo_ddr3_ctrl->PCCFG);//0x400

	/* port 0,1,2 en */
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_0);//0x490
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_1);//0x540
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_2);//0x5F0

	writel(0x00000000, &wokoo_ddr3_ctrl->DBG1);//0x304
	/* LPDDR2 DFI miscellaneous control reg */
	writel(0x00000030, &wokoo_ddr3_ctrl->DFIMISC);//0x1B0
	#else
	writel(0x00000011, &wokoo_ddr3_ctrl->DBG0);//0x300
    writel(0x00000000, &wokoo_ddr3_ctrl->DBG1);//0x304
    writel(0x00000000, &wokoo_ddr3_ctrl->DBGCMD);//0x30C
    writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);//0x320
    writel(0x00010010, &wokoo_ddr3_ctrl->POISONCFG);//0x36c
    writel(0x00000000, &wokoo_ddr3_ctrl->ADVECCINDEX);//0x374
    writel(0x00000000, &wokoo_ddr3_ctrl->ECCPOISONPAT0);//0x37c
    writel(0x00000000, &wokoo_ddr3_ctrl->ECCPOISONPAT2);//0x384	
	
	
	
	
	writel(0x00000000, &wokoo_ddr3_ctrl->PCCFG);//0x400
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGR_0);//0x404
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGR_1);//0x4B4
	
	
	
	
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGW_0);//0x408
	writel(0x0000400f, &wokoo_ddr3_ctrl->PCFGW_1);//0x4B8
	writel(0x00000001, &wokoo_ddr3_ctrl->PCCFG);//0x400

	/* port 0,1,2 en */
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_0);//0x490
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_1);//0x540
	writel(0x00000001, &wokoo_ddr3_ctrl->PCTRL_2);//0x5F0

	writel(0x00000000, &wokoo_ddr3_ctrl->DBG1);//0x304
	writel(0x00000002, &wokoo_ddr3_ctrl->PRWCTL);//0x030
	writel(0x00000000, &wokoo_ddr3_ctrl->SWCTL);
	
	/* LPDDR2 DFI miscellaneous control reg */
	writel(0x00000030, &wokoo_ddr3_ctrl->DFIMISC);//0x1B0
#endif
	

	 ddr3_PhyInitConfig();
	
	 ddr3_PhyInitMoniter();
     ddr3_PhyInitStart();
	
	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr3_ctrl->DFIMISC) | 0x00000001, &wokoo_ddr3_ctrl->DFIMISC);//0x1B0
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);//0x320
	
	ddr3_waitSWSTAT();
	
	/* reset */
	writel(0x02000000, &wokoo_ddr3_pwr->RESET);//0x038

	ddr3_waitSTATnormal();
	
	/* LPDDR2 refresh CTL3 */
	writel(readl(&wokoo_ddr3_ctrl->RFSHCTL3) | 0x00000001, &wokoo_ddr3_ctrl->RFSHCTL3);//0x060
	/* LPDDR2 low power powerdown_en */
	//writel(readl(&wokoo_ddr3_ctrl->PRWCTL) | 0x00000002, &wokoo_ddr3_ctrl->PRWCTL);// lsh 0x030
	 // writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);//0x320
	/* sw reg progam ctrl disable */
	writel(0x00000000, &wokoo_ddr3_ctrl->SWCTL);
	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr3_ctrl->DFIMISC) & ~0x00000001, &wokoo_ddr3_ctrl->DFIMISC);//0x1B0
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);

	//writel(readl(&wokoo_ddr3_phy->PGCR) | 0x08080000, &wokoo_ddr3_phy->PGCR);//0x008
	//writel(readl(&wokoo_ddr3_phy->PIR) | 0x00000180, &wokoo_ddr3_phy->PIR);//0x004
	
	ddr3_PhyInitDone();
	
	/* LPDDR2 refresh CTL3 */
	writel(readl(&wokoo_ddr3_ctrl->RFSHCTL3) & ~0x00000001, &wokoo_ddr3_ctrl->RFSHCTL3);//0x060
	/* LPDDR2 low power powerdown_en */
	writel(readl(&wokoo_ddr3_ctrl->PRWCTL) & ~0x00000002, &wokoo_ddr3_ctrl->PRWCTL);//0x030
	/* sw reg progam ctrl disable */
	writel(0x00000000, &wokoo_ddr3_ctrl->SWCTL);
	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr3_ctrl->DFIMISC) | 0x00000001, &wokoo_ddr3_ctrl->DFIMISC);
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr3_ctrl->SWCTL);
	printf("DDR3 init completed\n");

}



