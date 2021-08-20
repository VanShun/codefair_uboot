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
static struct wokoo_ddr_pwr  *wokoo_ddr_pwr  = (struct wokoo_ddr_pwr *)WOKOO_DDR_PWR_BASE;
static struct wokoo_ddr_ctrl *wokoo_ddr_ctrl = (struct wokoo_ddr_ctrl *)WOKOO_DDR_CTL_BASE;
static struct wokoo_ddr_phy  *wokoo_ddr_phy  = (struct wokoo_ddr_phy *)WOKOO_DDR_PHY_BASE;




/*
 *  ddr_PwrConfig - DDR PWR config
 *
 */
void ddr_PwrConfig(void)
{
	unsigned int data = 0;

	data = readl(&wokoo_ddr_pwr->PCLKEN) | 0x30003;
	writel(data, &wokoo_ddr_pwr->PCLKEN);

	data = readl(&wokoo_ddr_pwr->CLKEN0) | 0x0c030c03;
	writel(data, &wokoo_ddr_pwr->CLKEN0);

	data = (readl(&wokoo_ddr_pwr->ADDRCTL_CS0) | 0x000a030e) & 0xfffaffff;
	writel(data, &wokoo_ddr_pwr->ADDRCTL_CS0);

	data = (readl(&wokoo_ddr_pwr->ADDRCTL_CS1) | 0x000a030e) & 0xfffaffff;
	writel(data, &wokoo_ddr_pwr->ADDRCTL_CS1);
}

/*
 *  ddr_PhyInitConfig - DDR PHY config
 *
 */
void ddr_PhyInitConfig(void)
{
	unsigned int data = 0;

	data = readl(&wokoo_ddr_phy->PGCR);
	writel(0x018c2e02, &wokoo_ddr_phy->PGCR);

	data = readl(&wokoo_ddr_phy->DCR);
	writel(0x004, &wokoo_ddr_phy->DCR);

	data = readl(&wokoo_ddr_phy->DXCCR);
	writel(0xc40, &wokoo_ddr_phy->DXCCR);

	data = readl(&wokoo_ddr_phy->MR0);
	writel(0x421, &wokoo_ddr_phy->MR0);

	data = readl(&wokoo_ddr_phy->MR1);
	writel(0xc3, &wokoo_ddr_phy->MR1);

	data = readl(&wokoo_ddr_phy->MR2);
	writel(0x4, &wokoo_ddr_phy->MR2);

	data = readl(&wokoo_ddr_phy->MR3);
	writel(0x2, &wokoo_ddr_phy->MR3);

	data = readl(&wokoo_ddr_phy->DSGCR);
	writel(0xf800025f, &wokoo_ddr_phy->DSGCR);

	data = readl(&wokoo_ddr_phy->DTPR0);
	writel(0x409182ae, &wokoo_ddr_phy->DTPR0);

	data = readl(&wokoo_ddr_phy->DTPR1);
	writel(0x093300a0, &wokoo_ddr_phy->DTPR1);

	data = readl(&wokoo_ddr_phy->DTPR2);
	writel(0x10018c38, &wokoo_ddr_phy->DTPR2);
	
	data = data;
}

/*
 *  ddr_PhyInitMoniter - DDR PHY init moniter
 *
 */
void ddr_PhyInitMoniter(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	data = readl(&wokoo_ddr_phy->PTR0);
	writel(0x0020a688, &wokoo_ddr_phy->PTR0);
	writel(0x014130b4, &wokoo_ddr_phy->PTR1);
	writel(0x030e10c3, &wokoo_ddr_phy->PTR2);

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr_phy->PGSR);

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
void ddr_PhyInitStart(void)
{
	writel(0x00040001, &wokoo_ddr_phy->PIR);
}

/*
 *  ddr_PhyInitDone - DDR PHY init done
 *
 */
void ddr_PhyInitDone(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr_phy->PGSR);
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
void ddr_DFIInitDone(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr_ctrl->DFISTAT);
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
void ddr_waitSTATnormal(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr_ctrl->STAT);
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
void ddr_waitSWSTAT(void)
{
	unsigned int loop = 0;
	unsigned int data = 0;

	loop = 1;
	while (loop)
	{
		data = readl(&wokoo_ddr_ctrl->SWSTAT);
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
void ddr_init(void)
{
	/* DDR reset */
	writel(readl(&wokoo_ddr_pwr->RESET) | 0x3000300, &wokoo_ddr_pwr->RESET);
	//printf("DDR reset start\n");
	udelay(1000);
	writel((readl(&wokoo_ddr_pwr->RESET) | 0x3000000) & 0XFFFFFCFF, &wokoo_ddr_pwr->RESET);
	//printf("DDR reset completed\n");
	udelay(1000);

	ddr_PwrConfig();

	writel(0x02000200, &wokoo_ddr_pwr->RESET);
	writel(0x00000000, &wokoo_ddr_ctrl->SWCTL);

	writel(0x00000001, &wokoo_ddr_ctrl->DBG1);
	writel(0x00000001, &wokoo_ddr_ctrl->PRWCTL);

	/* LPDDR2|BURST_LEN_8|1 RANK 0x01040004 */
	writel(0x00040004, &wokoo_ddr_ctrl->MSTR);
	/* MRCTRL0|RANK 0|mrw 0x80000010;0x00000030 */
	writel(0x00000010, &wokoo_ddr_ctrl->MRCTRL0);

	/* MR63 addr = 3F(or F3?) --by hhc (MRCTRL1) */
	writel(0x00003f01, &wokoo_ddr_ctrl->MRCTRL1);
	/* LPDDR2 derating disable */
	writel(0x00000000, &wokoo_ddr_ctrl->DERATEEN);
	/* LPDDR2 MR4 read interval */
	writel(0xf829b026, &wokoo_ddr_ctrl->DERATEINT);
	/* LPDDR2 low power 0c00000002 powerdown_en */
	writel(0x00000000, &wokoo_ddr_ctrl->PRWCTL);

	/* LPDDR2 low power timing */
	writel(0x0040d904, &wokoo_ddr_ctrl->PWRTMG);

	writel(0x004b0002, &wokoo_ddr_ctrl->HWLPCTL);
	writel(0x00210000, &wokoo_ddr_ctrl->RFSHCTL0);
	writel(0x00000001, &wokoo_ddr_ctrl->RFSHCTL3);
#if 0
	writel(0x00c30024, &wokoo_ddr_ctrl->RFSHTMG);

	writel(0x00000010, &wokoo_ddr_ctrl->ECCCFG0);
	writel(0x00000000, &wokoo_ddr_ctrl->ECCCFG1);
	writel(0x00000000, &wokoo_ddr_ctrl->ECCCLR);
	writel(0x000000a0, &wokoo_ddr_ctrl->ECCPOISONADDR0);
	writel(0x01000d8a, &wokoo_ddr_ctrl->ECCPOISONADDR1);
	writel(0x00000000, &wokoo_ddr_ctrl->CRCPARCTL0);
#endif

	writel(0x00020002, &wokoo_ddr_ctrl->INIT0);
	writel(0x00010002, &wokoo_ddr_ctrl->INIT1);
	writel(0x00000e06, &wokoo_ddr_ctrl->INIT2);
	writel(0x00430004, &wokoo_ddr_ctrl->INIT3);
	writel(0x00020000, &wokoo_ddr_ctrl->INIT4);
	writel(0x000e0005, &wokoo_ddr_ctrl->INIT5);

	writel(0x00000000, &wokoo_ddr_ctrl->DIMMCTL);

	/* LPDDR2 sdram timing regX */
	writel(0x0e141a11, &wokoo_ddr_ctrl->DRAMTMG0);
	writel(0x0003061a, &wokoo_ddr_ctrl->DRAMTMG1);
	writel(0x03060b0b, &wokoo_ddr_ctrl->DRAMTMG2);
	writel(0x0050100c, &wokoo_ddr_ctrl->DRAMTMG3);
	writel(0x08010408, &wokoo_ddr_ctrl->DRAMTMG4);
	writel(0x02020606, &wokoo_ddr_ctrl->DRAMTMG5);
	writel(0x02020005, &wokoo_ddr_ctrl->DRAMTMG6);
	writel(0x00000202, &wokoo_ddr_ctrl->DRAMTMG7);
	writel(0x00000101, &wokoo_ddr_ctrl->DRAMTMG8);
	writel(0x00000028, &wokoo_ddr_ctrl->DRAMTMG14);
	writel(0x00000000, &wokoo_ddr_ctrl->DRAMTMG15);

	writel(0x40900024, &wokoo_ddr_ctrl->ZQCTL0);
	writel(0x014abfd4, &wokoo_ddr_ctrl->ZQCTL1);
	writel(0x02050103, &wokoo_ddr_ctrl->DFITMG0);
	writel(0x00030202, &wokoo_ddr_ctrl->DFITMG1);
	writel(0x07117101, &wokoo_ddr_ctrl->DFILPCFG0);
	writel(0x80280005, &wokoo_ddr_ctrl->DFIUPD0);
	writel(0x00a70026, &wokoo_ddr_ctrl->DFIUPD1);
	writel(0x00000000, &wokoo_ddr_ctrl->DFIUPD2);
	writel(0x00000031, &wokoo_ddr_ctrl->DFIMISC);
	writel(0x00000000, &wokoo_ddr_ctrl->DFIPHYMSTR);

	/* LPDDR2 addr map reg1 bank 31 */
#if 0
	writel(0x001f1f1f, &wokoo_ddr_ctrl->ADDRMAP0);
	writel(0x003f0707, &wokoo_ddr_ctrl->ADDRMAP1);
#else
	//writel(0x001f1f1f, &wokoo_ddr_ctrl->ADDRMAP0);
	writel(0x003f0707 | readl(&wokoo_ddr_ctrl->ADDRMAP1), &wokoo_ddr_ctrl->ADDRMAP1);
#endif
	/* LPDDR2 addr map reg2 col */
	writel(0x00000000, &wokoo_ddr_ctrl->ADDRMAP2);
	/* LPDDR2 addr map reg3 col */
	writel(0x1f000000, &wokoo_ddr_ctrl->ADDRMAP3);
	/* LPDDR2 addr map reg4 col */
	writel(0x00001f1f, &wokoo_ddr_ctrl->ADDRMAP4);
	/* LPDDR2 addr map reg5 row */
	writel(0x05050505, &wokoo_ddr_ctrl->ADDRMAP5);
	/* LPDDR2 addr map reg6 row */
	writel(0x0f0f0f05, &wokoo_ddr_ctrl->ADDRMAP6);
	writel(0x001f1f05, &wokoo_ddr_ctrl->ADDRMAP11);

	/* LPDDR2 ODT config reg */
	writel(0x06010710, &wokoo_ddr_ctrl->ODTCFG);
	/* LPDDR2 ODT/rank map reg */
	writel(0x00000000, &wokoo_ddr_ctrl->ODTMAP);
	/* LPDDR2 scheduler control reg */
	writel(0x03080805, &wokoo_ddr_ctrl->SCHED);
	writel(0x00000000, &wokoo_ddr_ctrl->SCHED1);
	writel(0x0f000001, &wokoo_ddr_ctrl->PERFHPR1);
	writel(0x0f00007f, &wokoo_ddr_ctrl->PERFLPR1);
	writel(0x0f00007f, &wokoo_ddr_ctrl->PERFWR1);

#if 0
	writel(0x00000011, &wokoo_ddr_ctrl->DBG0);
	writel(0x00000000, &wokoo_ddr_ctrl->DBG1);
	writel(0x00000000, &wokoo_ddr_ctrl->DBGCMD);
	writel(0x00000001, &wokoo_ddr_ctrl->SWCTL);
	writel(0x00010010, &wokoo_ddr_ctrl->POISONCFG);
	writel(0x00000000, &wokoo_ddr_ctrl->ADVECCINDEX);
	writel(0x00000000, &wokoo_ddr_ctrl->ECCPOISONPAT0);
	writel(0x00000000, &wokoo_ddr_ctrl->ECCPOISONPAT2);
#endif

	/* PCCFG/port common cfg reg */
	writel(0x00000000, &wokoo_ddr_ctrl->PCCFG);
	writel(0x0000400f, &wokoo_ddr_ctrl->PCFGR_0);
	writel(0x0000400f, &wokoo_ddr_ctrl->PCFGR_1);
	writel(0x0000400f, &wokoo_ddr_ctrl->PCFGW_0);
	writel(0x0000400f, &wokoo_ddr_ctrl->PCFGW_1);
	writel(0x00000001, &wokoo_ddr_ctrl->PCCFG);

	/* port 0,1,2 en */
	writel(0x00000001, &wokoo_ddr_ctrl->PCTRL_0);
	writel(0x00000001, &wokoo_ddr_ctrl->PCTRL_1);
	writel(0x00000001, &wokoo_ddr_ctrl->PCTRL_2);

	writel(0x00000000, &wokoo_ddr_ctrl->DBG1);
	/* LPDDR2 DFI miscellaneous control reg */
	writel(0x00000030, &wokoo_ddr_ctrl->DFIMISC);

	ddr_PhyInitConfig();
	ddr_PhyInitMoniter();
	ddr_PhyInitStart();

	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr_ctrl->DFIMISC) | 0x00000001, &wokoo_ddr_ctrl->DFIMISC);
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr_ctrl->SWCTL);

	ddr_waitSWSTAT();
	/* reset */
	writel(0x02000000, &wokoo_ddr_pwr->RESET);
	ddr_waitSTATnormal();

	/* LPDDR2 refresh CTL3 */
	writel(readl(&wokoo_ddr_ctrl->RFSHCTL3) | 0x00000001, &wokoo_ddr_ctrl->RFSHCTL3);
	/* LPDDR2 low power powerdown_en */
	writel(readl(&wokoo_ddr_ctrl->PRWCTL) | 0x00000002, &wokoo_ddr_ctrl->PRWCTL);
	/* sw reg progam ctrl disable */
	writel(0x00000000, &wokoo_ddr_ctrl->SWCTL);
	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr_ctrl->DFIMISC) & ~0x00000001, &wokoo_ddr_ctrl->DFIMISC);
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr_ctrl->SWCTL);

	writel(readl(&wokoo_ddr_phy->PGCR) | 0x08080000, &wokoo_ddr_phy->PGCR);
	writel(readl(&wokoo_ddr_phy->PIR) | 0x00000180, &wokoo_ddr_phy->PIR);

	ddr_PhyInitDone();

	/* LPDDR2 refresh CTL3 */
	writel(readl(&wokoo_ddr_ctrl->RFSHCTL3) & ~0x00000001, &wokoo_ddr_ctrl->RFSHCTL3);
	/* LPDDR2 low power powerdown_en */
	writel(readl(&wokoo_ddr_ctrl->PRWCTL) & ~0x00000002, &wokoo_ddr_ctrl->PRWCTL);
	/* sw reg progam ctrl disable */
	writel(0x00000000, &wokoo_ddr_ctrl->SWCTL);
	/* LPDDR2 DFI miscellaneous control reg */
	writel(readl(&wokoo_ddr_ctrl->DFIMISC) | 0x00000001, &wokoo_ddr_ctrl->DFIMISC);
	/* sw reg progam ctrl enable */
	writel(0x00000001, &wokoo_ddr_ctrl->SWCTL);
}



