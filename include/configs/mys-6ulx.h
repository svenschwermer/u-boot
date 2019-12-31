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

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Default environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"fitaddr=0x84000000\0" \
	"image=fitImage\0" \
	"netboot=echo Booting over the network ...; " \
            "setenv bootargs root=/dev/nfs nfsroot=/srv/nfs/mys_rfs ip=dhcp console=ttymxc0,115200; " \
	    "dhcp ${fitaddr} ${image}; " \
	    "bootm ${fitaddr};\0"

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

#ifdef CONFIG_MTD_RAW_NAND
# define CONFIG_SYS_MAX_NAND_DEVICE 1
#endif

/* SPL */
#ifdef CONFIG_SPL
# ifdef CONFIG_MXC_UART
#  define CONFIG_MXC_UART_BASE		UART1_BASE
# endif
# ifdef CONFIG_FSL_ESDHC
#  define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC1_BASE_ADDR
# endif
# include "imx6_spl.h"
#endif

#endif /* __MYS_6ULX_CONFIG_H */
