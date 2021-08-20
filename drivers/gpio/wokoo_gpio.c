/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
 *		http://www.codefairsemi.com 
 *
 */

#include <common.h>
#include <errno.h>
#include <dm.h>
#include <malloc.h>
#include <asm/gpio.h>
#include <asm/arch-wokoo/wokoo_gpio.h>
#include <asm/io.h>




enum wokoo_gpio_direction {
	WOKOO_GPIO_DIRECTION_IN,
	WOKOO_GPIO_DIRECTION_OUT,
};

struct wokoo_gpio_platdata {
	struct wokoo_gpio	*base;
};

#define GPIO_TO_PORT(n)		((n) / 16)
#define GPIO_TO_GPIO(n)		((n) % 16)




/*
 *  wokoo_gpio_set_direction - set gpio direction
 *
 *  @gpio: gpio
 *  @direction: direction
 */
static int wokoo_gpio_set_direction(struct wokoo_gpio *base, unsigned int gpio,
	enum wokoo_gpio_direction direction)
{
	u32 l, port, io;
	
	if (gpio >= 128)
		return -1;

	port = GPIO_TO_PORT(gpio);
	io   = GPIO_TO_GPIO(gpio);
	/* Write able bit = io + 16 */
	l    = readl(&base->PORT_DDR[port]) | (1 << (io + 16));

	switch (direction) {
	case WOKOO_GPIO_DIRECTION_OUT:
		l |= 1 << io;
		break;
	case WOKOO_GPIO_DIRECTION_IN:
		l &= ~(1 << io);
	}

	writel(l, &base->PORT_DDR[port]);

	return 0;
}

/*
 *  wokoo_gpio_set_value - set gpio output value
 *
 *  @gpio: gpio
 *  @value: value
 */
static int wokoo_gpio_set_value(struct wokoo_gpio *base, unsigned gpio, int value)
{
	u32 l, port, io;

	if (gpio >= 128)
		return -1;

	port = GPIO_TO_PORT(gpio);
	io   = GPIO_TO_GPIO(gpio);
	/* Write able bit = io + 16 */
	l    = readl(&base->PORT_DR[port]) | (1 << (io + 16));

	if (value)
		l |= 1 << io;
	else
		l &= ~(1 << io);
	writel(l, &base->PORT_DR[port]);

	return 0;
}

/*
 *  gpio_get_value - get gpio input value
 *
 *  @gpio: gpio
 *  @return: gpio value
 */
static int wokoo_gpio_get_value(struct wokoo_gpio *base, unsigned gpio)
{
	u32 val, port, io;

	if (gpio >= 128)
		return -1;

	port = gpio / 32;
	io   = gpio % 32;

	val  = (readl(&base->EXT_PORT[port]) >> io) & 0x1;
	return val;
}

#ifndef CONFIG_DM_GPIO
/* GPIO base addr */
static struct wokoo_gpio *base = (struct wokoo_gpio *)WOKOO_GPIO_BASE;

int gpio_set_value(unsigned gpio, int value)
{
	return wokoo_gpio_set_value(base, gpio, value);
}

int gpio_get_value(unsigned gpio)
{
	return wokoo_gpio_get_value(base, gpio);
}

int gpio_request(unsigned gpio, const char *label)
{
	if (gpio >= 128)
		return -1;

	return 0;
}

int gpio_free(unsigned gpio)
{
	return 0;
}

int gpio_direction_input(unsigned gpio)
{
	return wokoo_gpio_set_direction(base, gpio, WOKOO_GPIO_DIRECTION_IN);
}

int gpio_direction_output(unsigned gpio, int value)
{
	int ret = wokoo_gpio_set_direction(base, gpio, WOKOO_GPIO_DIRECTION_OUT);

	if (ret < 0)
		return ret;

	return gpio_set_value(gpio, value);
}
#else
static int wokoo_dm_gpio_direction_input(struct udevice *dev, unsigned offset)
{
	struct wokoo_gpio_platdata *platdata = dev_get_platdata(dev);

	return wokoo_gpio_set_direction(platdata->base, offset, WOKOO_GPIO_DIRECTION_IN);
}

static int wokoo_dm_gpio_direction_output(struct udevice *dev, unsigned offset,
				int value)
{
	struct wokoo_gpio_platdata *platdata = dev_get_platdata(dev);
	int ret = wokoo_gpio_set_direction(platdata->base, offset, WOKOO_GPIO_DIRECTION_OUT);

	if (ret < 0)
		return ret;

	return wokoo_gpio_set_value(platdata->base, offset, value);
}

static int wokoo_dm_gpio_get_value(struct udevice *dev, unsigned offset)
{
	struct wokoo_gpio_platdata *platdata = dev_get_platdata(dev);

	return wokoo_gpio_get_value(platdata->base, offset);
}

static int wokoo_dm_gpio_set_value(struct udevice *dev, unsigned offset, int value)
{
	struct wokoo_gpio_platdata *platdata = dev_get_platdata(dev);

	return wokoo_gpio_set_value(platdata->base, offset, value);
}

static const struct dm_gpio_ops gpio_wokoo_ops = {
	.direction_input  = wokoo_dm_gpio_direction_input,
	.direction_output = wokoo_dm_gpio_direction_output,
	.get_value        = wokoo_dm_gpio_get_value,
	.set_value        = wokoo_dm_gpio_set_value,
};

static const struct udevice_id wokoo_gpio_ids[] = {
	{ .compatible = "wokoo,wokoo-gpio0"},
	{ }
};

static int wokoo_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);

	uc_priv->bank_name  = dev->name;
	uc_priv->gpio_count = 127;

	return 0;
}

static int wokoo_gpio_ofdata_to_platdata(struct udevice *dev)
{
	struct wokoo_gpio_platdata *platdata = dev_get_platdata(dev);

	platdata->base = (struct wokoo_gpio *)dev_read_addr(dev);

	return 0;
}

U_BOOT_DRIVER(gpio_wokoo) = {
	.name	= "gpio_wokoo",
	.id	= UCLASS_GPIO,
	.ops	= &gpio_wokoo_ops,
	.of_match = wokoo_gpio_ids,
	.ofdata_to_platdata = wokoo_gpio_ofdata_to_platdata,
	.probe	= wokoo_gpio_probe,
	.platdata_auto_alloc_size = sizeof(struct wokoo_gpio_platdata),
};
#endif

