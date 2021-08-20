/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#ifndef _WOKOO_MUX_H_
#define _WOKOO_MUX_H_




struct wokoo_mux {
	uint32_t MUX[8];			/*!< Offset: 0x000~0x01C  PIN MUX register */
	uint32_t reserved0[8];		/*!< Offset: 0x020~0x03C  reserved register*/
	uint32_t TST_PIN_CTRL0;		/*!< Offset: 0x040  PIN test control register 0 */
	uint32_t TST_PIN_CTRL1;		/*!< Offset: 0x044  PIN test control register 1 */
	uint32_t reserved1[10];		/*!< Offset: 0x048~0x06C  reserved register */
	uint32_t PULL_EN[4];		/*!< Offset: 0x070~0x7C  PIN pull control register */
	uint32_t reserved2[36];		/*!< Offset: 0x080~0x10C  reserved register*/
	uint32_t INPUT_EN[4];		/*!< Offset: 0x110~0x11C  PIN input control register */
};


/* MUXPIN_MUX0 */
#define WOKOO_PIN__GPIO83__PMURST                0
#define WOKOO_PIN__GPIO84__PMUEN                 2
#define WOKOO_PIN__GPIO85__OSC_EN_3V             4
#define WOKOO_PIN__GPIO86__CLK_OUT0              6
#define WOKOO_PIN__GPIO87__CLK_OUT1              8
#define WOKOO_PIN__GPIO88__CLK_OUT2              10
#define WOKOO_PIN__GPIO89__CLK_OUT3              12
#define WOKOO_PIN__GPIO90__PMU_DVFS0             14
#define WOKOO_PIN__GPIO91__PMU_DVFS1             16
#define WOKOO_PIN__GPIO92__USB_DRVVBUS           18
#define WOKOO_PIN__GPIO93__PWM0                  20
#define WOKOO_PIN__GPIO94__PWM1                  22
#define WOKOO_PIN__GPIO95__PWM2                  24
#define WOKOO_PIN__GPIO96__PWM3                  26

/* MUXPIN_MUX1 */
#define WOKOO_PIN__GPIO32__ISP_SCLK              32
#define WOKOO_PIN__GPIO33__ISP_SCLK0             34
#define WOKOO_PIN__GPIO34__ISP_RST_N0            36
#define WOKOO_PIN__GPIO35__ISP_PWM               38
#define WOKOO_PIN__GPIO36__ISP_STROBE            40
#define WOKOO_PIN__GPIO37__ISP_S_HSYNC           42
#define WOKOO_PIN__GPIO38__ISP_S_VSYNC           44
#define WOKOO_PIN__GPIO39__GPIO39                46
#define WOKOO_PIN__GPIO40__GPIO40                48
#define WOKOO_PIN__GPIO41__ISP_PDWN_N0           50
#define WOKOO_PIN__GPIO42__ISP_FSIN0             52

/* MUXPIN_MUX2 */
#define WOKOO_PIN__GPIO43__ISP_S_DATA0           64
#define WOKOO_PIN__GPIO44__ISP_S_DATA1           66
#define WOKOO_PIN__GPIO45__ISP_S_DATA2           68
#define WOKOO_PIN__GPIO46__ISP_S_DATA3           70
#define WOKOO_PIN__GPIO47__ISP_S_DATA4           72
#define WOKOO_PIN__GPIO48__ISP_S_DATA5           74
#define WOKOO_PIN__GPIO49__ISP_S_DATA6           76
#define WOKOO_PIN__GPIO50__ISP_S_DATA7           78
#define WOKOO_PIN__GPIO51__ISP_S_DATA8           80
#define WOKOO_PIN__GPIO52__ISP_S_DATA9           82

/* MUXPIN_MUX3 */
#define WOKOO_PIN__GPIO53__UART0_TX              96
#define WOKOO_PIN__GPIO54__UART0_RX              98
#define WOKOO_PIN__GPIO55__UART0_CTX             100
#define WOKOO_PIN__GPIO56__UART0_RTX             102
#define WOKOO_PIN__GPIO57__UART1_TX              104
#define WOKOO_PIN__GPIO58__UART1_RX              106
#define WOKOO_PIN__GPIO59__UART1_CTX             108
#define WOKOO_PIN__GPIO60__UART1_RTX             110
#define WOKOO_PIN__GPIO61__UART2_TX              112
#define WOKOO_PIN__GPIO62__UART2_RX              114
#define WOKOO_PIN__GPIO63__UART2_CTX             116
#define WOKOO_PIN__GPIO64__UART2_RTX             118

/* MUXPIN_MUX4 */
#define WOKOO_PIN__GPIO65__SSI0_TX               128
#define WOKOO_PIN__GPIO66__SSI0_RX               130
#define WOKOO_PIN__GPIO67__SSI0_CLK              132
#define WOKOO_PIN__GPIO68__SSI0_SSN1             134
#define WOKOO_PIN__GPIO69__SSI0_SSN0             136
#define WOKOO_PIN__GPIO70__I2S0_WS               138
#define WOKOO_PIN__GPIO71__I2S0_SCLK             140
#define WOKOO_PIN__GPIO72__I2S0_SDOUT            142
#define WOKOO_PIN__GPIO73__I2S0_SDIN             144
#define WOKOO_PIN__GPIO74__I2C0_SCL              146
#define WOKOO_PIN__GPIO75__I2C0_SDA              148
#define WOKOO_PIN__GPIO76__I2C1_SCL              150
#define WOKOO_PIN__GPIO77__I2C1_SDA              152

/* MUXPIN_MUX5 */
#define WOKOO_PIN__GPIO78__JTAG_TCK              160
#define WOKOO_PIN__GPIO79__JTAG_TDI              162
#define WOKOO_PIN__GPIO80__JTAG_TDO              164
#define WOKOO_PIN__GPIO81__JTAG_TMS              166
#define WOKOO_PIN__GPIO82__JTAG_TRST             168
#define WOKOO_PIN__GPIO97__ISP_S_DATA10          170
#define WOKOO_PIN__GPIO98__ISP_S_DATA11          172
#define WOKOO_PIN__GPIO99__LCDC_CSM_N            174
#define WOKOO_PIN__GPIO100__LCDC_CSS_N           176
#define WOKOO_PIN__GPIO101__LCDC_A0              178
#define WOKOO_PIN__GPIO102__LCDC_WR_N            180
#define WOKOO_PIN__GPIO103__LCDC_RD_N            182
#define WOKOO_PIN__GPIO104__LCDC_DATOUT_EN       184
#define WOKOO_PIN__GPIO105__LCDC_DATOUT_0        186
#define WOKOO_PIN__GPIO106__LCDC_DATOUT_1        188
#define WOKOO_PIN__GPIO107__LCDC_DATOUT_2        190

/* MUXPIN_MUX6 */
#define WOKOO_PIN__GPIO108__LCDC_DATOUT_3        192
#define WOKOO_PIN__GPIO109__LCDC_DATOUT_4        194
#define WOKOO_PIN__GPIO110__LCDC_DATOUT_5        196
#define WOKOO_PIN__GPIO111__LCDC_DATOUT_6        198
#define WOKOO_PIN__GPIO112__LCDC_DATOUT_7        200
#define WOKOO_PIN__GPIO113__LCDC_DATOUT_8        202
#define WOKOO_PIN__GPIO114__LCDC_DATOUT_9        204
#define WOKOO_PIN__GPIO115__LCDC_DATOUT_10       206
#define WOKOO_PIN__GPIO116__LCDC_DATOUT_11       208
#define WOKOO_PIN__GPIO117__LCDC_DATOUT_12       210
#define WOKOO_PIN__GPIO118__LCDC_DATOUT_13       212
#define WOKOO_PIN__GPIO119__LCDC_DATOUT_14       214
#define WOKOO_PIN__GPIO120__LCDC_DATOUT_15       216
#define WOKOO_PIN__GPIO121__LCDC_DATOUT_16       218
#define WOKOO_PIN__GPIO122__LCDC_DATOUT_17       220
#define WOKOO_PIN__GPIO123__LCDC_DATOUT_18       222

/* MUXPIN_MUX7 */
#define WOKOO_PIN__GPIO124__LCDC_DATOUT_19       224
#define WOKOO_PIN__GPIO125__LCDC_DATOUT_20       226
#define WOKOO_PIN__GPIO126__LCDC_DATOUT_21       228
#define WOKOO_PIN__GPIO127__LCDC_DATOUT_22       230
#define WOKOO_PIN__GPIO128__LCDC_DATOUT_23       232
#define WOKOO_PIN__GPIO28__I2S1_WS               234
#define WOKOO_PIN__GPIO29__I2S1_SCLK             236
#define WOKOO_PIN__GPIO30__I2S1_SDOUT            238
#define WOKOO_PIN__GPIO31__I2S1_SDIN             240


#define WOKOO_MUX_MASK                           0x3
#define WOKOO_MUX_GPIO                           0x2
#define WOKOO_MUX_FUNC                           0x0

#define WOKOO_MUX_PIN_SET_GPIO(__base__, __pin__)  \
( __base__->MUX[(__pin__) / 32] &= ~(WOKOO_MUX_MASK << ((__pin__) % 32)), \
  __base__->MUX[(__pin__) / 32] |=   WOKOO_MUX_GPIO << ((__pin__) % 32) )

#define WOKOO_MUX_PIN_SET_FUNC(__base__, __pin__)  \
( __base__->MUX[(__pin__) / 32] &= ~(WOKOO_MUX_MASK << ((__pin__) % 32)), \
  __base__->MUX[(__pin__) / 32] |=   WOKOO_MUX_FUNC << ((__pin__) % 32) )

/* 0 enable pull, 1 disable pull */
#define WOKOO_MUX_PIN_SET_PULL(__base__, __gpion__, __enable__) \
( __base__->PULL_EN[(__gpion__) / 32] &= ~(0x1 << ((__gpion__) % 32)), \
  __base__->PULL_EN[(__gpion__) / 32] |= (!__enable__) << ((__gpion__) % 32) )

#define WOKOO_MUX_PIN_SET_INPUT(__base__, __gpion__, __enable__) \
( __base__->INPUT_EN[(__gpion__) / 32] &= ~(0x1 << ((__gpion__) % 32)), \
  __base__->INPUT_EN[(__gpion__) / 32] |= (__enable__) << ((__gpion__) % 32) )


#define WOKOO_MUX_BASE                           0xA0153000





#endif /* _WOKOO_GPIO_H_ */

