/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_DMA_H_
#define _WOKOO_DMA_H_




struct wokoo_dmag {
	uint32_t CH_STATUS;			/*!< Offset: 0x00 channel status register */
	uint32_t CH03_PRIOR;		/*!< Offset: 0x04 channel0 ~ channel3 priority control register */
	uint32_t reserved0;			/*!< Offset: 0x08 reserved registers   */
	uint32_t CH_INTR_EN_A7;		/*!< Offset: 0x0C channel Cortex-A7 interrupt enable register */
	uint32_t CH_INTR_STATUS_A7; /*!< Offset: 0x10 channel Cortex-A7 interrupt status register */
	uint32_t reserved1[2];		/*!< Offset: 0x14~0x18  reserved registers */
	uint32_t CH_INTR_MASK_A7;	/*!< Offset: 0x1C channel Cortex-A7 interrupt mask register */
	uint32_t reserved2[11];		/*!< Offset: 0x20~0x48  reserved registers */
	uint32_t CH_LP_EN;			/*!< Offset: 0x4C channel low power mode enable register */
	uint32_t AHB_LP_EN;			/*!< Offset: 0x50 AHB interface low power mode enable register */
};

struct wokoo_dma_channel {
	uint32_t CHX_CTL;			/*!< Offset: 0x100 + (N-1)*0x40 channel x control register */
	uint32_t CHX_SIZE;			/*!< Offset: 0x104 + (N-1)*0x40 channel x data size register */
	uint32_t CHX_PARA;			/*!< Offset: 0x108 + (N-1)*0x40 channel x param register */
	uint32_t CHX_SRC_ADDR;		/*!< Offset: 0x10C + (N-1)*0x40 channel x source address register */
	uint32_t CHX_DST_ADDR;		/*!< Offset: 0x110 + (N-1)*0x40 channel x destination start address register */
	uint32_t CHX_INTR_EN;		/*!< Offset: 0x114 + (N-1)*0x40 channel x interrupt enable register */
	uint32_t CHX_INTR_STATUS;	/*!< Offset: 0x118 + (N-1)*0x40 channel x interrupt status register */
	uint32_t CHX_INTR_RAW;		/*!< Offset: 0x11C + (N-1)*0x40 channel x interrupt raw status register */
	uint32_t CHX_CUR_SRC_ADDR;	/*!< Offset: 0x120 + (N-1)*0x40 channel x current source address register */
	uint32_t CHX_CUR_DST_ADDR;	/*!< Offset: 0x124 + (N-1)*0x40 channel x current destination address register */
	uint32_t CHX_SPACE;			/*!< Offset: 0x128 + (N-1)*0x40 channel x address interval register */
	uint32_t reserved[5];		/*!< Offset: 0x12C~0x13C + (N-1)*0x40  reserved registers*/
};

typedef struct DMA_CONFIG
{
	uint32_t	x_size;
	uint32_t	y_size;
	void		*src;
	void		*dst;
	uint32_t	src_space;
	uint32_t	dst_space;
} dma_config_t;



#define WOKOO_DMAG_BASE				0xA0000000
#define WOKOO_DMA_CHANNEL_BASE(x)	(WOKOO_DMAG_BASE + 0x100 + 0x40 * (x))




int  dma_status_is_err(int channel);
int  dma_is_transfer_end(int channel);
void dma_reset(int channel);
void dma_clear_transfer_end(int channel);
void dma_transfer(int channel, dma_config_t *config);
int  dma_calc_transfer_size(int size, dma_config_t *config);



#endif /* _WOKOO_DDR_H_ */


