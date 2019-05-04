// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019 Sven Schwermer
 */
#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch-mx6/clock.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_FEC_MXC
static int enable_eth_clk(void)
{
	int ret;
	struct iomuxc *const iomuxc_regs = (struct iomuxc *)IOMUXC_BASE_ADDR;

	ret = enable_fec_anatop_clock(0, ENET_50MHZ);
	if (ret)
		return ret;

	/*
	 * Use 50M anatop loopback REF_CLK1 for ENET1,
	 * clear gpr1[13], set gpr1[17].
	 */
	clrsetbits_le32(&iomuxc_regs->gpr[1], IOMUX_GPR1_FEC1_MASK,
		IOMUX_GPR1_FEC1_CLOCK_MUX1_SEL_MASK);

	return 0;
}
#endif

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_FEC_MXC
	enable_eth_clk();
#endif

	return 0;
}
