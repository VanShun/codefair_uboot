/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <bootm.h>
#include <common.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/arch-wokoo/clock.h>
#include <ipu_pixfmt.h>
#include <thermal.h>




extern u32 get_cpu_speed_grade_hz(void);

unsigned wokoo_ddr_size(void)
{
#if defined(CONFIG_WOKOO_DDR3)

	return 0x8000000;
#else
    return 0x2000000;
#endif
}

#if defined(CONFIG_DISPLAY_CPUINFO) && !defined(CONFIG_SPL_BUILD)
int print_cpuinfo(void)
{
	printf("CPU:   Wokoo rev%d.%d at %d MHz (running at %d MHz)\n",
		1, 0, get_cpu_speed_grade_hz() / 1000,
		wokoo_get_clock(WOKOO_ARM_CLK) / 1000);


	return 0;
}
#endif

int cpu_eth_init(bd_t *bis)
{
	int rc = -ENODEV;

	return rc;
}

void arch_preboot_os(void)
{
}

