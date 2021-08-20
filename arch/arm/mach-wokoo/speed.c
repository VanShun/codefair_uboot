/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <asm/arch-wokoo/clock.h>




#ifdef CONFIG_FSL_ESDHC_IMX
DECLARE_GLOBAL_DATA_PTR;
#endif

int get_clocks(void)
{
	return 0;
}
