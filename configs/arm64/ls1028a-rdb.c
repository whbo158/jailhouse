/*
 * ls1028a RDB target - linux-demo
 *
 * Copyright 2020-2021 NXP
 *
 * Authors:
 *  Hongbo Wang <hongbo.wang@nxp.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[75];
	struct jailhouse_irqchip irqchips[3];
	struct jailhouse_pci_device pci_devices[2];
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
			.address = 0x21c0500, /* Uart0 in DUART1 */
			.size = 0x100,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				 JAILHOUSE_CON_REGDIST_1,
		},
		.platform_info = {
			.pci_mmconfig_base = 0xc0700000,
			.pci_mmconfig_end_bus = 0,
			.pci_is_virtual = 1,
			.pci_domain = -1,

			.arm = {
				.gic_version = 3,
				.gicd_base = 0x06000000,
				.gicr_base = 0x06040000,
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "ls1028a",
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.vpci_irq_base = 108 - 32, /* Not include 32 base */
		},
	},

	.cpus = {
		0x3,
	},

	.mem_regions = {
		/* IVSHMEM shared memory region for 00:00.0 */ {
			.phys_start = 0xc0500000,
			.virt_start = 0xc0500000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ,
		},
		{
			.phys_start = 0xc0501000,
			.virt_start = 0xc0501000,
			.size = 0x9000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		{
			.phys_start = 0xc050a000,
			.virt_start = 0xc050a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		{
			.phys_start = 0xc050c000,
			.virt_start = 0xc050c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ,
		},
		{
			.phys_start = 0xc050e000,
			.virt_start = 0xc050e000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ,
		},
		/* IVSHMEM shared memory regions for 00:01.0 (networking) */
		JAILHOUSE_SHMEM_NET_REGIONS(0xc0600000, 0),
		/* RAM - 1GB at DRAM1 region - root cell */ {
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* RAM: Inmate */ {
			.phys_start = 0xc0900000,
			.virt_start = 0xc0900000,
			.size = 0x33700000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* RAM: loader */ {
			.phys_start = 0xc0400000,
			.virt_start = 0xc0400000,
			.size = 0x00100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* DDR memory controller */ {
			.phys_start = 0x01080000,
			.virt_start = 0x01080000,
			.size =	          0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
                /* ClockGen */ {
                        .phys_start = 0x01300000,
                        .virt_start = 0x01300000,
                        .size = 0xa0000,
                        .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                                JAILHOUSE_MEM_IO,
                },
		/* DCFG */ {
			.phys_start = 0x01e00000,
			.virt_start = 0x01e00000,
			.size =	         0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* RCPM */ {
			.phys_start = 0x01e30000,
			.virt_start = 0x01e30000,
			.size =	         0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* TMU */ {
			.phys_start = 0x01f80000,
			.virt_start = 0x01f80000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SCFG */ {
			.phys_start = 0x01fc0000,
			.virt_start = 0x01fc0000,
			.size =	         0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 1 */ {
			.phys_start = 0x02000000,
			.virt_start = 0x02000000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 2 */ {
			.phys_start = 0x02010000,
			.virt_start = 0x02010000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 3 */ {
			.phys_start = 0x02020000,
			.virt_start = 0x02020000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 4 */ {
			.phys_start = 0x02030000,
			.virt_start = 0x02030000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 5 */ {
			.phys_start = 0x02040000,
			.virt_start = 0x02040000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 6 */ {
			.phys_start = 0x02050000,
			.virt_start = 0x02050000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 7 */ {
			.phys_start = 0x02060000,
			.virt_start = 0x02060000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 8 */ {
			.phys_start = 0x02070000,
			.virt_start = 0x02070000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* FlexSPI */ {
			.phys_start = 0x020c0000,
			.virt_start = 0x020c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPI 1 */ {
			.phys_start = 0x02100000,
			.virt_start = 0x02100000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPI 2 */ {
			.phys_start = 0x02110000,
			.virt_start = 0x02110000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPI 3 */ {
			.phys_start = 0x02120000,
			.virt_start = 0x02120000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* eSDHC1 */ {
			.phys_start = 0x02140000,
			.virt_start = 0x02140000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* eSDHC2 */ {
			.phys_start = 0x02150000,
			.virt_start = 0x02150000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* CAN1 */ {
			.phys_start = 0x02180000,
			.virt_start = 0x02180000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* CAN2 */ {
			.phys_start = 0x02190000,
			.virt_start = 0x02190000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DUART 1 */ {
			.phys_start = 0x021c0000,
			.virt_start = 0x021c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 1 */ {
			.phys_start = 0x02260000,
			.virt_start = 0x02260000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 2 */ {
			.phys_start = 0x02270000,
			.virt_start = 0x02270000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 3 */ {
			.phys_start = 0x02280000,
			.virt_start = 0x02280000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 4 */ {
			.phys_start = 0x02290000,
			.virt_start = 0x02290000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 5 */ {
			.phys_start = 0x022a0000,
			.virt_start = 0x022a0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LPUART 6 */ {
			.phys_start = 0x022b0000,
			.virt_start = 0x022b0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* eDMA MUX1 MUX2 */ {
			.phys_start = 0x022c0000,
			.virt_start = 0x022c0000,
			.size = 0x30000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPIO 1 */ {
			.phys_start = 0x02300000,
			.virt_start = 0x02300000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPIO 2 */ {
			.phys_start = 0x02310000,
			.virt_start = 0x02310000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPIO 3 */ {
			.phys_start = 0x02320000,
			.virt_start = 0x02320000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* USB 1 */ {
			.phys_start = 0x03100000,
			.virt_start = 0x03100000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* USB 2 */ {
			.phys_start = 0x03110000,
			.virt_start = 0x03110000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SATA */ {
			.phys_start = 0x03200000,
			.virt_start = 0x03200000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIE1 */ {
			.phys_start = 0x03400000,
			.virt_start = 0x03400000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIE1 PF0 */ {
			.phys_start = 0x034c0000,
			.virt_start = 0x034c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIE2 */ {
			.phys_start = 0x03500000,
			.virt_start = 0x03500000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIE2 PF0 */ {
			.phys_start = 0x035c0000,
			.virt_start = 0x035c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* CCI-400 */ {
			.phys_start = 0x04090000,
			.virt_start = 0x04090000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* IOMMU */ {
			.phys_start = 0x05000000,
			.virt_start = 0x05000000,
			.size = 0x800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GITS */ {
			.phys_start = 0x06020000,
			.virt_start = 0x06020000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SEC-crypto */ {
			.phys_start = 0x08000000,
			.virt_start = 0x08000000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* qDMA */ {
			.phys_start = 0x08380000,
			.virt_start = 0x08380000,
			.size = 0x60000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* core0-watchdog */ {
			.phys_start = 0x0c000000,
			.virt_start = 0x0c000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* core1-watchdog */ {
			.phys_start = 0x0c010000,
			.virt_start = 0x0c010000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LCD */ {
			.phys_start = 0x0f080000,
			.virt_start = 0x0f080000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPU */ {
			.phys_start = 0x0f0c0000,
			.virt_start = 0x0f0c0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 1 */ {
			.phys_start = 0x0f100000,
			.virt_start = 0x0f100000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 2 */ {
			.phys_start = 0x0f110000,
			.virt_start = 0x0f110000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 3 */ {
			.phys_start = 0x0f120000,
			.virt_start = 0x0f120000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 4 */ {
			.phys_start = 0x0f130000,
			.virt_start = 0x0f130000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 5 */ {
			.phys_start = 0x0f140000,
			.virt_start = 0x0f140000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SAI 6 */ {
			.phys_start = 0x0f150000,
			.virt_start = 0x0f150000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* EDP PHY */ {
			.phys_start = 0x0f200000,
			.virt_start = 0x0f200000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* for root cell */ {
			.phys_start = 0xf4000000,
			.virt_start = 0xf4000000,
			.size = 0xc000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* for root cell pcie */ {
			.phys_start = 0x1f0000000,
			.virt_start = 0x1f0000000,
			.size = 0xd000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* for root cell */ {
			.phys_start = 0x700100000,
			.virt_start = 0x700100000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* System RAM */ {
			.phys_start = 0x2080000000,
			.virt_start = 0x2080000000,
			.size = 0x80000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* MEM */ {
			.phys_start = 0x8040000000,
			.virt_start = 0x8040000000,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* MEM */ {
			.phys_start = 0x8840000000,
			.virt_start = 0x8840000000,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0x06000000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
		/* GIC */ {
			.address = 0x06000000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
		/* GIC */ {
			.address = 0x06000000,
			.pin_base = 288,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
	},

	.pci_devices = {
		{ /* IVSHMEM 00:00.0 (demo) */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0,
			.bdf = 0 << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
			.shmem_regions_start = 0,
			.shmem_dev_id = 0,
			.shmem_peers = 3,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_UNDEFINED,
		},
		{ /* IVSHMEM 00:01.0 (networking) */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0,
			.bdf = 1 << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
			.shmem_regions_start = 5,
			.shmem_dev_id = 0,
			.shmem_peers = 2,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
	},
};
