# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (c) 2020 Codefair Semiconductor Technology Co., Ltd.
#		http://www.codefairsemi.com 
#
#

ifeq ($(SOC),$(filter $(SOC),wokoo))
obj-y	+= cpu.o speed.o usbotg.o
endif
ifeq ($(SOC),$(filter $(SOC),wokoo))
obj-y	+= misc.o 
obj-$(CONFIG_SPL_BUILD)	+= spl.o
endif
ifeq ($(SOC),$(filter $(SOC),wokoo))
obj-y 	+= cache.o init.o

obj-$(CONFIG_SECURE_BOOT)    += hab.o
obj-$(CONFIG_SYSCOUNTER_TIMER) += syscounter.o
endif

PLUGIN = board/$(BOARDDIR)/plugin

ifeq ($(CONFIG_USE_IMXIMG_PLUGIN),y)

$(PLUGIN).o: $(PLUGIN).S FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,as_o_S)

$(PLUGIN).bin: $(PLUGIN).o FORCE
	$(Q)mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --gap-fill 0xff $< $@
else

$(PLUGIN).bin:

endif

quiet_cmd_cpp_cfg = CFGS    $@
	cmd_cpp_cfg = $(CPP) $(cpp_flags) -x c -o $@ $<

# mkimage source config file
WOKOO_CONFIG = $(CONFIG_WOKOO_CONFIG:"%"=%)

# How to create a cpp processed config file, they all use the same source
%.cfgout: $(IMX_CONFIG) FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,cpp_cfg)

IMAGE_TYPE := wokooimage
DEPFILE_EXISTS := 0

MKIMAGEFLAGS_u-boot.wokoo = -n $(filter-out $(PLUGIN).bin $< $(PHONY),$^) \
	-T $(IMAGE_TYPE) -e $(CONFIG_SYS_TEXT_BASE)
u-boot.imx: MKIMAGEOUTPUT = u-boot.wokoo.log

u-boot.imx: u-boot.bin u-boot.cfgout $(PLUGIN).bin FORCE
	$(call if_changed,mkimage)

ifeq ($(CONFIG_MULTI_DTB_FIT),y)
MKIMAGEFLAGS_u-boot-dtb.wokoo = -n $(filter-out $(PLUGIN).bin $< $(PHONY),$^) \
	-T $(IMAGE_TYPE) -e $(CONFIG_SYS_TEXT_BASE)
u-boot-dtb.wokoo: MKIMAGEOUTPUT = u-boot-dtb.wokoo.log

u-boot-dtb.wokoo: u-boot-fit-dtb.bin u-boot-dtb.cfgout $(PLUGIN).bin FORCE
ifeq ($(DEPFILE_EXISTS),0)
	$(call if_changed,mkimage)
endif
else ifeq ($(CONFIG_OF_SEPARATE),y)
MKIMAGEFLAGS_u-boot-dtb.wokoo = -n $(filter-out $(PLUGIN).bin $< $(PHONY),$^) \
	-T $(IMAGE_TYPE) -e $(CONFIG_SYS_TEXT_BASE)
u-boot-dtb.wokoo: MKIMAGEOUTPUT = u-boot-dtb.wokoo.log

u-boot-dtb.wokoo: u-boot-dtb.bin u-boot-dtb.cfgout $(PLUGIN).bin FORCE
ifeq ($(DEPFILE_EXISTS),0)
	$(call if_changed,mkimage)
endif
endif

MKIMAGEFLAGS_SPL = -n $(filter-out $(PLUGIN).bin $< $(PHONY),$^) \
			-T $(IMAGE_TYPE) -e $(CONFIG_SPL_TEXT_BASE)
SPL: MKIMAGEOUTPUT = SPL.log

SPL: spl/u-boot-spl.bin spl/u-boot-spl.cfgout $(PLUGIN).bin FORCE
	$(call if_changed,mkimage)

MKIMAGEFLAGS_u-boot.uim = -A arm -O U-Boot -a $(CONFIG_SYS_TEXT_BASE) \
		-e $(CONFIG_SYS_TEXT_BASE) -C none -T firmware

u-boot.uim: u-boot.bin FORCE
	$(call if_changed,mkimage)

OBJCOPYFLAGS += -I binary -O binary --pad-to=$(CONFIG_SPL_PAD_TO)
append = cat $(filter-out $< $(PHONY), $^) >> $@

quiet_cmd_pad_cat = CAT     $@
cmd_pad_cat = $(cmd_objcopy) && $(append) || rm -f $@

u-boot-with-spl.wokoo: SPL u-boot.uim FORCE
	$(call if_changed,pad_cat)

u-boot-with-nand-spl.wokoo: spl/u-boot-nand-spl.wokoo u-boot.uim FORCE
	$(call if_changed,pad_cat)

quiet_cmd_u-boot-nand-spl_wokoo = GEN     $@
cmd_u-boot-nand-spl_wokoo = (printf '\000\000\000\000\106\103\102\040\001' && \
	dd bs=1015 count=1 if=/dev/zero 2>/dev/null) | cat - $< > $@

spl/u-boot-nand-spl.wokoo: SPL FORCE
	$(call if_changed,u-boot-nand-spl_wokoo)

targets += $(addprefix ../../../,SPL spl/u-boot-spl.cfgout u-boot-dtb.cfgout u-boot.cfgout u-boot.uim spl/u-boot-nand-spl.wokoo)
obj-$(CONFIG_WOKOO) += wokoo/
