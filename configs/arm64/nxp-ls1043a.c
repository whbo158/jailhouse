/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for NXP LS1043ARDB board
 *
 * Copyright (c) NXP, 2019
 *
 * Authors:
 *  hongbo.wang <hongbo.wang@nxp.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[52];
	struct jailhouse_irqchip irqchips[2];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xc0000000,
			.size =       0x00400000,
		},

		.debug_console = {
			.address = 0x021c0500,
			.size = 0x100,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				JAILHOUSE_CON_REGDIST_1,
		},

		.platform_info = {
			.arm = {
				.gic_version = 2,
				.gicd_base = 0x1401000,
				.gicc_base = 0x1402000,
				.gich_base = 0x1404000,
				.gicv_base = 0x1406000,
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "nxp-ls1043a",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
		},
	},

	.cpus = {
		0xf,
	},

	.mem_regions = {
		/* DDR memory controller */ {
			.phys_start = 0x01080000,
			.virt_start = 0x01080000,
			.size =	          0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* IFC */ {
			.phys_start = 0x01530000,
			.virt_start = 0x01530000,
			.size =	         0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* QSPI */ {
			.phys_start = 0x01550000,
			.virt_start = 0x01550000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* esdhc */ {
			.phys_start = 0x01560000,
			.virt_start = 0x01560000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* scfg */ {
			.phys_start = 0x01570000,
			.virt_start = 0x01570000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* crypto */ {
			.phys_start = 0x01700000,
			.virt_start = 0x01700000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* qman */ {
			.phys_start = 0x01880000,
			.virt_start = 0x01880000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
                /* bman */ {
                        .phys_start = 0x01890000,
                        .virt_start = 0x01890000,
                        .size = 0x10000,
                        .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                                JAILHOUSE_MEM_IO,
                },
		/* fman */ {
			.phys_start = 0x01a00000,
			.virt_start = 0x01a00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* dcfg */ {
			.phys_start = 0x01ee0000,
			.virt_start = 0x01ee0000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
                /* clockgen */ {
                        .phys_start = 0x01ee1000,
                        .virt_start = 0x01ee1000,
                        .size = 0x1000,
                        .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                                JAILHOUSE_MEM_IO,
                },
		/* rcpm */ {
			.phys_start = 0x01ee2000,
			.virt_start = 0x01ee2000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* tmu */ {
			.phys_start = 0x01f00000,
			.virt_start = 0x01f00000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* dspi */ {
			.phys_start = 0x02100000,
			.virt_start = 0x02100000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* i2c0 */ {
			.phys_start = 0x02180000,
			.virt_start = 0x02180000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* i2c1 */ {
			.phys_start = 0x02190000,
			.virt_start = 0x02190000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* i2c2 */ {
			.phys_start = 0x021a0000,
			.virt_start = 0x021a0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* i2c3 */ {
			.phys_start = 0x021b0000,
			.virt_start = 0x021b0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* duart1 */ {
			.phys_start = 0x021c0000,
			.virt_start = 0x021c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* duart2 */ {
			.phys_start = 0x021d0000,
			.virt_start = 0x021d0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* gpio0 */ {
			.phys_start = 0x02300000,
			.virt_start = 0x02300000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* gpio1 */ {
			.phys_start = 0x02310000,
			.virt_start = 0x02310000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* gpio2 */ {
			.phys_start = 0x02320000,
			.virt_start = 0x02320000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* gpio3 */ {
			.phys_start = 0x02330000,
			.virt_start = 0x02330000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart0 */ {
			.phys_start = 0x02950000,
			.virt_start = 0x02950000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart1 */ {
			.phys_start = 0x02960000,
			.virt_start = 0x02960000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart2 */ {
			.phys_start = 0x02970000,
			.virt_start = 0x02970000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart3 */ {
			.phys_start = 0x02980000,
			.virt_start = 0x02980000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart4 */ {
			.phys_start = 0x02990000,
			.virt_start = 0x02990000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* lpuart5 */ {
			.phys_start = 0x029a0000,
			.virt_start = 0x029a0000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* timer */ {
			.phys_start = 0x029d0000,
			.virt_start = 0x029d0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* wdog0 */ {
			.phys_start = 0x02ad0000,
			.virt_start = 0x02ad0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* edma0 */ {
			.phys_start = 0x02c00000,
			.virt_start = 0x02c00000,
			.size = 0x30000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* usb0 */ {
			.phys_start = 0x02f00000,
			.virt_start = 0x02f00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* usb1 */ {
			.phys_start = 0x03000000,
			.virt_start = 0x03000000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* usb2 */ {
			.phys_start = 0x03100000,
			.virt_start = 0x03100000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* sata */ {
			.phys_start = 0x03200000,
			.virt_start = 0x03200000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* pcie0 */ {
			.phys_start = 0x03400000,
			.virt_start = 0x03400000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* pcie1 */ {
			.phys_start = 0x03500000,
			.virt_start = 0x03500000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* pcie2 */ {
			.phys_start = 0x03600000,
			.virt_start = 0x03600000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* sata-ecc */ {
			.phys_start = 0x20140500,
			.virt_start = 0x20140500,
			.size = 0x100,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* nor */ {
			.phys_start = 0x60000000,
			.virt_start = 0x60000000,
			.size = 0x8000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* RAM - 1GB - root cell */ {
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* RAM - ~1GB - inmates */ {
			.phys_start = 0xc0500000,
			.virt_start = 0xc0500000,
			.size = 0x3fb00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* qportals CE */ {
			.phys_start = 0x500000000,
			.virt_start = 0x500000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* qportals CI */ {
			.phys_start = 0x504000000,
			.virt_start = 0x504000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* bportals CE */ {
			.phys_start = 0x508000000,
			.virt_start = 0x508000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* bportals CI */ {
			.phys_start = 0x50c000000,
			.virt_start = 0x50c000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCI host bridge 0 */ {
			.phys_start = 0x4000000000,
			.virt_start = 0x4000000000,
			.size = 0x800000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCI host bridge 1 */ {
			.phys_start = 0x4800000000,
			.virt_start = 0x4800000000,
			.size = 0x800000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCI host bridge 2 */ {
			.phys_start = 0x5000000000,
			.virt_start = 0x5000000000,
			.size = 0x800000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* IVSHMEM shared memory region for 00:00.0 */ {
			.phys_start = 0xc0400000,
			.virt_start = 0xc0400000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0x1410000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
		/* GIC */ {
			.address = 0x1410000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
        },
};
