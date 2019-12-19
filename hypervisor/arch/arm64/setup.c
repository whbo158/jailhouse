/*
 * Jailhouse AArch64 support
 *
 * Copyright (C) 2015 Huawei Technologies Duesseldorf GmbH
 *
 * Authors:
 *  Antonios Motakis <antonios.motakis@huawei.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/cell.h>
#include <jailhouse/entry.h>
#include <jailhouse/paging.h>
#include <jailhouse/printk.h>
#include <jailhouse/processor.h>
#include <asm/control.h>
#include <asm/entry.h>
#include <asm/irqchip.h>
#include <asm/setup.h>
#include <asm/smccc.h>

extern u8 __trampoline_start[];

int arch_init_early(void)
{
	unsigned long trampoline_page = paging_hvirt2phys(&__trampoline_start);
	int err;

	/*
	 * ID-map the trampoline code page.
	 *
	 * We will need it for shutting down once the final page table is
	 * installed. So better do this early while we can still handle errors.
	 */
	err = paging_create(&hv_paging_structs, trampoline_page, PAGE_SIZE,
			    trampoline_page, PAGE_DEFAULT_FLAGS,
			    PAGING_NON_COHERENT);
	if (err)
		return err;

	return arm_init_early();
}

int arch_cpu_init(struct per_cpu *cpu_data)
{
	unsigned long hcr = HCR_VM_BIT | HCR_IMO_BIT | HCR_FMO_BIT
				| HCR_TSC_BIT | HCR_TAC_BIT | HCR_RW_BIT;
	int err;

printk("WHB arch_cpu_init 0\n");
	/* link to ID-mapping of trampoline page */
	err = paging_create_hvpt_link(&cpu_data->pg_structs,
				      paging_hvirt2phys(&__trampoline_start));
	if (err)
		return err;

printk("WHB arch_cpu_init 1\n");
	/* switch to the permanent page tables */
	enable_mmu_el2(paging_hvirt2phys(cpu_data->pg_structs.root_table));

	/* Setup guest traps */
	arm_write_sysreg(HCR_EL2, hcr);

	err = arm_cpu_init(cpu_data);
	if (err)
		return err;

printk("WHB arch_cpu_init 2\n");
	/* Conditionally switch to hardened vectors */
	if (this_cpu_data()->smccc_has_workaround_1)
		arm_write_sysreg(vbar_el2, &hyp_vectors_hardened);

	return 0;
}

void __attribute__((noreturn)) arch_cpu_activate_vmm(void)
{
	unsigned int cpu_id = this_cpu_id();
printk("WHB arch_cpu_activate_vmm 00\n");
	/*
	 * Switch the stack to the private mapping before deactivating the
	 * common one.
	 */
#if 0
	asm volatile(
		"add sp, sp, %0"
		: : "g" (LOCAL_CPU_BASE - (unsigned long)per_cpu(cpu_id)));
#endif
printk("WHB arch_cpu_activate_vmm 11\n");
	/* Revoke full per_cpu access now that everything is set up. */
//	paging_map_all_per_cpu(cpu_id, false);

printk("WHB arch_cpu_activate_vmm 22\n");
	/* return to the caller in Linux */
//	arm_write_sysreg(ELR_EL2, this_cpu_data()->guest_regs.usr[30]);

printk("WHB arch_cpu_activate_vmm 33\n");
//	vmreturn(&this_cpu_data()->guest_regs);
printk("WHB arch_cpu_activate_vmm 44\n");
}

#define READ_REG(r, f) if (f || (pregs[r] == 0)) {asm volatile("str x"#r", %0" : "=m" (pregs[r]));}
static void copy_reg_value(unsigned long *pregs)
{
	READ_REG(0, true)
	READ_REG(1, true)
	READ_REG(2, true)
	READ_REG(3, true)
	READ_REG(4, true)
	READ_REG(5, true)
	READ_REG(6, true)
	READ_REG(7, true)
	READ_REG(8, true)
	READ_REG(9, true)
	READ_REG(10, true)
	READ_REG(11, true)
	READ_REG(12, true)
	READ_REG(13, true)
	READ_REG(14, true)
	READ_REG(15, true)
	READ_REG(16, true)
	READ_REG(17, true)
	READ_REG(18, true)
	READ_REG(19, false)

#if 1
	READ_REG(20, false)
	READ_REG(21, false)
	READ_REG(22, false)
	READ_REG(23, false)
	READ_REG(24, false)
	READ_REG(25, false)
	READ_REG(26, false)
	READ_REG(27, false)
	READ_REG(28, false)
	READ_REG(29, false)
	READ_REG(30, false)
#endif
}

extern unsigned int master_cpu_id;
void  arch_cpu_activate_vmmwhb(void)
{
	int i = 0;
	unsigned int cpu_id = this_cpu_id();
printk("WHB arch_cpu_activate_vmm 00\n");
	/*
	 * Switch the stack to the private mapping before deactivating the
	 * common one.
	 */
#if 1
	asm volatile(
		"add sp, sp, %0"
		: : "g" (LOCAL_CPU_BASE - (unsigned long)per_cpu(cpu_id)));
#endif
printk("WHB arch_cpu_activate_vmm 11\n");
	/* Revoke full per_cpu access now that everything is set up. */
//	paging_map_all_per_cpu(cpu_id, false);

printk("WHB arch_cpu_activate_vmm 22\n");

	copy_reg_value(this_cpu_data()->guest_regs.usr);

	/* return to the caller in Linux */
	arm_write_sysreg(ELR_EL2, this_cpu_data()->guest_regs.usr[30]);
	if (1) {
		for (i = 0; i < NUM_USR_REGS; i++) {
			printk("c%d-x%d:%lx\n", cpu_id, i, this_cpu_data()->guest_regs.usr[i]);
		}
	}

printk("WHB arch_cpu_activate_vmm 33\n");
//	vmreturn(&this_cpu_data()->guest_regs);
printk("WHB arch_cpu_activate_vmm 44\n");
}

/* disable the hypervisor on the current CPU */
void arch_shutdown_self(struct per_cpu *cpu_data)
{
	void (*shutdown_func)(struct per_cpu *) =
		(void (*)(struct per_cpu *))paging_hvirt2phys(shutdown_el2);

	irqchip_cpu_shutdown(&cpu_data->public);

	/* Free the guest */
	arm_write_sysreg(HCR_EL2, HCR_RW_BIT);
	arm_write_sysreg(VTCR_EL2, VTCR_RES1);

	/* Remove stage-2 mappings */
	arm_paging_vcpu_flush_tlbs();

	/* TLB flush needs the cell's VMID */
	isb();
	arm_write_sysreg(VTTBR_EL2, 0);

	/* we will restore the root cell state with the MMU turned off,
	 * so we need to make sure it has been committed to memory */
	arch_paging_flush_cpu_caches(cpu_data, sizeof(*cpu_data));
	dsb(ish);

	/* hand over control of EL2 back to Linux */
	asm volatile("msr vbar_el2, %0"
		:: "r" (hypervisor_header.arm_linux_hyp_vectors));

	/* Return to EL1 */
	shutdown_func((struct per_cpu *)paging_hvirt2phys(cpu_data));
}

void arch_cpu_restore(unsigned int cpu_id, int return_code)
{
	struct per_cpu *cpu_data = per_cpu(cpu_id);

	/* Jailhouse initialization failed; return to the caller in EL1 */
	arm_write_sysreg(ELR_EL2, cpu_data->guest_regs.usr[30]);

	cpu_data->guest_regs.usr[0] = return_code;

	arch_shutdown_self(cpu_data);
}
