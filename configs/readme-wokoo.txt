编译配置说明:
	configs/wokoo_codefair_app_defconfig
		支持引导裸机程序，或RTOS系统程序，启动偏移0x8000,下载占用uImager的位置。
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可	
		Lingh：基础上增加一个宏开关，只需要烧写u-boot_spl.bin就可以，然后app烧写地址还是在0x8000，目前支持app大小为4M，如果需要超过需要修改codefair.h里面的配置。
		
	configs/wokoo_codefair_ddr3_defconfig
		支持DDR3 1G bit大容量内存。
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可
		Lingh：基于wokoo_codefair_defconfig,在其上增加一个宏开关,需要烧写 u-boot_spl.bin和u-boot ，唯一区别是他走的是ddr3_init的初始化，环境变量size的大小128M，如果后期需要支持更大那还需要修改这个size，设备树使用的是同一个。
	
	configs/wokoo_codefair_defconfig
		？需说明
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可

	configs/wokoo_codefair_dm_defconfig
		不可用，不发布
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可
		Lingh：大部分驱动支持。dm: device manage（UART,SPI，SSI，USB ）, USB gagdet 可支持DM，但是这个配置没配，原因是DM host/gadget同时开启时，gadget DM会无法我给使用，DM模式下支持SPL，自动根据跳线引导SSI/SPI, 支持u-boot上烧写SSI/QSPI, 通过setenv spidev spi0.0/spi1.0来更改烧写的flash.
		
	configs/wokoo_codefair_mini_defconfig
		? 需说明
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可
		Lingh：针对小系统的配置文件，内核启动速度控制0.8s以内，但是支持wokoo所有的驱动，包括v4l2相关的驱动，文件系统只支持jffs2及cramfs，是针对扫码小系统而制作，因此不适合其它特殊的应用，这个系统不支持自动创建设备结点，因此对应的文件系统要自己建好相关的节点（只读的cramfs文件系统），非只读的文件系统可以执行mdev -s来自动创建设备结点。
			mini rootfs 这个文件系统是与wokoo_mini_defconfig相配合的文件系统，这个文件系统是最简的系统，只包含裁减的busybox(绝大部分命令可用，去除的网络相关的命令)，rx/rz, 及相关的库文件，可根据需要制作成jffs2或cramfs。
	configs/wokoo_codefair_mini_ssi_defconfig
		? 需说明
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   可
		Lingh：针对8Mflash及快速（2S内）启动系统，ssi是配置为SSI引导的配置，否则是QSPI引导的，这个配置针对性删减了u-boot的功能，所以配置的u-boot的对应的命令是很少，命令基本上只满足加载linux及flash的烧写，有配套的内核和文件系统与这个配置配套使用。
	
	configs/wokoo_codefair_dm_ssi_defconfig
		? 需说明
		uboot放QSPI flash 可用否？  可
		uboot放SSI flash 可用否？   从ssi启动，烧写 （Liuyz）

