/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for NXP FSL-LS1043A-RDB board
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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[7];
	struct jailhouse_irqchip irqchips[2];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xb7c00000,
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
				.gicd_base = 0x1410000,
				.gicc_base = 0x142f000,
				.gich_base = 0x1440000,
				.gicv_base = 0x146f000,
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "ls1046a",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
		},
	},

	.cpus = {
		0xf,
	},

	.mem_regions = {
		/* RAM 00*/ {
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size = 0x33c00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* Inmate memory */{
			.phys_start = 0xb3c00000,
			.virt_start = 0xb3c00000,
			.size = 0x04000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* RAM 01 */ {
			.phys_start = 0xb8000000,
			.virt_start = 0xb8000000,
			.size = 0x03700000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* Loader */{
			.phys_start = 0xbb700000,
			.virt_start = 0xbb700000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* IVHSMEM shared memory region for 00:00.0 */ {
			.phys_start = 0xbba00000,
			.virt_start = 0xbba00000,
			.size = 0x200000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE ,
		},
		/* RAM 02 */ {
			.phys_start = 0xbbc00000,
			.virt_start = 0xbbc00000,
			.size = 0x02400000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* reserved memory */{
			.phys_start = 0xbe000000,
			.virt_start = 0xbe000000,
			.size = 0x2000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0x1400000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
		/* GIC */ {
			.address = 0x1400000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
        },
};
