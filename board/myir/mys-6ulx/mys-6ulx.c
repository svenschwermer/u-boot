// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019 Sven Schwermer
 */
#include <common.h>
#include <asm/arch/sys_proto.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
    gd->ram_size = imx_ddr_size();
    return 0;
}

int board_init(void)
{
    gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;
    return 0;
}
