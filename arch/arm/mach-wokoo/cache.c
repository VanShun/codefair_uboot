// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 */

#include <common.h>
#include <asm/armv7.h>
#include <asm/pl310.h>
#include <asm/io.h>

static void enable_ca7_smp(void)
{
	u32 val;

	/* Read MIDR */
	asm volatile ("mrc p15, 0, %0, c0, c0, 0\n\t" : "=r"(val));
	val = (val >> 4);
	val &= 0xf;

	/* Only set the SMP for Cortex A7 */
	if (val == 0x7) {
		/* Read auxiliary control register */
		asm volatile ("mrc p15, 0, %0, c1, c0, 1\n\t" : "=r"(val));

		if (val & (1 << 6))
			return;

		/* Enable SMP */
		val |= (1 << 6);

		/* Write auxiliary control register */
		asm volatile ("mcr p15, 0, %0, c1, c0, 1\n\t" : : "r"(val));

		DSB;
		ISB;
	}
}

#if !CONFIG_IS_ENABLED(SYS_DCACHE_OFF)
void enable_caches(void)
{
#if defined(CONFIG_SYS_ARM_CACHE_WRITETHROUGH)
	enum dcache_option option = DCACHE_WRITETHROUGH;
#else
	enum dcache_option option = DCACHE_WRITEBACK;
#endif
	/* Avoid random hang when download by usb */
	invalidate_dcache_all();

	/* Set ACTLR.SMP bit for Cortex-A7 */
	enable_ca7_smp();

	/* Enable D-cache. I-cache is already enabled in start.S */
	dcache_enable();

	/* Enable caching on OCRAM and ROM */
	mmu_set_region_dcache_behaviour(ROMCP_ARB_BASE_ADDR,
					ROMCP_ARB_SIZE,
					option);
	mmu_set_region_dcache_behaviour(IRAM_BASE_ADDR,
					IRAM_SIZE,
					option);
}
#else
void enable_caches(void)
{
	/*
	 * Set ACTLR.SMP bit for Cortex-A7, even if the caches are
	 * disabled by u-boot
	 */
	enable_ca7_smp();

	puts("WARNING: Caches not enabled\n");
}
#endif

