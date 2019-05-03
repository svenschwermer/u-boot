/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2019 Sven Schwermer
 *
 * Configuration settings for the MYiR MYS-6ULX boards
 */

#ifndef __MYS_6ULX_CONFIG_H
#define __MYS_6ULX_CONFIG_H

#include "mx6_common.h"

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

/* Total Size of Environment Sector */
#define CONFIG_ENV_SIZE			SZ_128K

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Default environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"splashpos=m,m\0" \
	"image=uImage\0" \
	"fit_image=fit.itb\0" \
	"fdt_high=0xffffffff\0" \
	"fdt_addr=0x87800000\0" \
	"boot_fdt=try\0" \
	"mmcpart=1\0" \
	"recovery_device=0\0" \
	"recovery_part=2\0" \
	"recovery_root=/dev/mmcblk0p2 rootwait rw\0" \
	"nandroot=ubi0:rootfs rootfstype=ubifs\0" \
	"mmcautodetect=yes\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot}\0" \
	"recovery_mmcargs= setenv bootargs console=${console},${baudrate} "\
		"root=${recovery_root}\0" \
	"ubiargs=setenv bootargs console=${console},${baudrate} " \
		"ubi.mtd=5 root=${nandroot} ${mtdparts}\0" \
	"loadbootscript=" \
		"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"recovery_loadimage=ext2load mmc ${recovery_device}:${recovery_part} ${loadaddr} ${image}\0" \
	"recovery_loadfdt=ext2load mmc ${recovery_device}:${recovery_part} ${fdt_addr} ${fdt_file}\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"loadfit=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${fit_image}\0" \
	"altbootcmd=run recovery_boot\0"\
	"recovery_boot=echo Recovery Boot from mmc ...; " \
		"run recovery_loadimage ; run recovery_loadfdt; run recovery_mmcargs; "\
		"bootm ${loadaddr} - ${fdt_addr}\0" \
	"fitboot=echo Booting FIT image from mmc ...; " \
		"run mmcargs; " \
		"bootm ${loadaddr}\0" \
	"_mmcboot=run mmcargs; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootm ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootm; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootm; " \
		"fi\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"if mmc rescan; then " \
			"if run loadbootscript; then " \
				"run bootscript; " \
			"else " \
				"if run loadfit; then " \
					"run fitboot; " \
				"else " \
					"if run loadimage; then " \
						"run _mmcboot; " \
					"fi; " \
				"fi; " \
			"fi; " \
		"fi\0" \
	"nandboot=echo Booting from nand ...; " \
		"if mtdparts; then " \
			"echo Starting nand boot ...; " \
		"else " \
			"mtdparts default; " \
		"fi; " \
		"run ubiargs; " \
		"nand read ${loadaddr} kernel 0x800000; " \
		"nand read ${fdt_addr} dtb 0x100000; " \
		"bootm ${loadaddr} - ${fdt_addr}\0"

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

/* Physical Memory Map */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_SP_OFFSET)

#ifdef CONFIG_USB_EHCI_MX6
# define CONFIG_MXC_USB_PORTSC (PORT_PTS_UTMI | PORT_PTS_PTW)
#endif

/* SPL */
#ifdef CONFIG_SPL
# include "imx6_spl.h"
# define CONFIG_MXC_UART_BASE		UART1_BASE
#endif

#endif /* __MYS_6ULX_CONFIG_H */
