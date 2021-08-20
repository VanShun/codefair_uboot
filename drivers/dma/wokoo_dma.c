/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <asm/io.h>
#include <common.h>
#include <asm/arch-wokoo/wokoo_dma.h>



int dma_status_is_err(int channel)
{
	struct wokoo_dma_channel *base = (struct wokoo_dma_channel *)WOKOO_DMA_CHANNEL_BASE(channel);

	if (readl(&base->CHX_INTR_STATUS) & 0x40)
		return 1;
	else
		return 0;
}

void dma_clear_transfer_end(int channel)
{
	uint32_t regval;
	struct wokoo_dma_channel *base = (struct wokoo_dma_channel *)WOKOO_DMA_CHANNEL_BASE(channel);

	regval 	= readl(&base->CHX_INTR_STATUS);
	regval |= 0x01;
	writel(regval, &base->CHX_INTR_STATUS);
}

int dma_is_transfer_end(int channel)
{
	uint32_t regval;
	struct wokoo_dma_channel *base = (struct wokoo_dma_channel *)WOKOO_DMA_CHANNEL_BASE(channel);

	regval 	= readl(&base->CHX_INTR_STATUS);

	return regval & 0x01;
}

void dma_reset(int channel)
{
	struct wokoo_dma_channel *base = (struct wokoo_dma_channel *)WOKOO_DMA_CHANNEL_BASE(channel);

	writel(0x04, &base->CHX_CTL);
}

int dma_calc_transfer_size(int size, dma_config_t *config)
{
	int i;
	int remain = 0;

	if (size <= 65535){
		config->x_size = size;
		config->y_size = 1;
		remain = 0;
	} else {
		for (i = 1; i < 16; i++) {
			config->y_size = 1 << i;
			config->x_size = size >> i;

			if (config->x_size <= 65535) {
				break;
			}
		}

		remain = size % (1 << i);
	}

	return remain;
}

void dma_transfer(int channel, dma_config_t *config)
{
	uint32_t regval;
	struct wokoo_dmag *dmag_base   = (struct wokoo_dmag *)WOKOO_DMAG_BASE;
	struct wokoo_dma_channel *base = (struct wokoo_dma_channel *)WOKOO_DMA_CHANNEL_BASE(channel);

	regval 	= readl(&base->CHX_INTR_EN);
	regval |= 0x01;
	writel(regval, &base->CHX_INTR_EN);

	regval 	= readl(&dmag_base->CH_INTR_EN_A7);
	regval |= 0x01 << channel;
	writel(regval, &dmag_base->CH_INTR_EN_A7);

	regval = (config->y_size << 16) + (config->x_size & 0x0000FFFF);
	writel(regval, &base->CHX_SIZE);

	regval = readl(&base->CHX_PARA);
	regval = (regval & 0xFFF0FFFF) | 0x00050000;
	writel(regval, &base->CHX_PARA);

	writel((uint32_t)(config->src), &base->CHX_SRC_ADDR);
	writel((uint32_t)(config->dst), &base->CHX_DST_ADDR);

	regval = (config->dst_space << 16) + (config->src_space & 0x0000FFFF);
	writel(regval, &base->CHX_SPACE);

	writel(0x01, &base->CHX_CTL);
}
