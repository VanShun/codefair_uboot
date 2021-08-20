/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <asm/io.h>
#include <div64.h>
#include <asm/arch/clock.h>
#include <asm/arch-wokoo/wokoo_timer.h>




DECLARE_GLOBAL_DATA_PTR;

static struct wokoo_timer *base = (struct wokoo_timer *)WOKOO_TIMER_BASE;
static u32 timer_tick = 0;

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
void timer0_config_mode_auto(void)
{
	/* Timer crossover value is 20 default */
	/* 1ms tick = freq / 1000  = freq Khz  */
	timer_tick = get_bus_clk() / 20;

	/* Disable timer0 */
	writel(readl(&base->TCR) & 0xFE, &base->TCR);
	/* Set custom mode */
	writel(readl(&base->TCR) | 0x02, &base->TCR);
	writel(timer_tick, &base->TLC);
	/* Disable int */
	writel(readl(&base->TCR) | 0x04, &base->TCR);
	/* Enable timer0 */
	writel(readl(&base->TCR) | 0x01, &base->TCR);
	//AP_TIMER0_TCR |= 0x01;
	gd->arch.timer_reset_value = timer_tick;
}

int timer_init(void)
{
	timer0_config_mode_auto();
	gd->arch.lastinc = 0;
	gd->arch.tbu = 0;
	gd->arch.timer_rate_hz = CONFIG_SYS_HZ;
	return 0;
}
#endif

u32 getTimerCoun(void)
{
	return readl(&base->TCV);
}

unsigned long long get_ticks(void)
{
	u32 now = readl(&base->TCV);

	/* increment tbu if tbl has rolled over */
	if (now > gd->arch.lastinc) {
		gd->arch.tbu++;
	}

	//printf("get_ticks  tbu = %ld, lastinc = %ld, now = %ld\n", gd->arch.tbu, gd->arch.lastinc, now);
	gd->arch.lastinc = now;

	/* tbu * 1ms << 32 |  ticks */
	return (((unsigned long long)gd->arch.tbu) << 32) | gd->arch.lastinc;
}

ulong get_timer(ulong base)
{
	ulong timer = 0;
	unsigned long long timer_diff;

	timer_diff = get_ticks();
	timer = (timer_diff >> 32) - base;

	return timer;
}

void __udelay(unsigned long usec)
{
	unsigned long long endtime;

	/* n * 1ms << 32 | usec * timer_tick / 1000 (1us ticks) */
	endtime = ((unsigned long long)(usec / CONFIG_SYS_HZ) << 32)
	| ((usec % CONFIG_SYS_HZ) * gd->arch.timer_reset_value  / CONFIG_SYS_HZ);
	endtime += get_ticks();

	while (get_ticks() < endtime)
		;
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
	return gd->arch.timer_rate_hz;
}
