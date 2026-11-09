#ifndef PSX_HW_EXTRA_H
#define PSX_HW_EXTRA_H

#include "psx/mem.h"

/* The hardware seam: HW_REF and HW_PTR reach the PS1 MMIO window. The BIOS vector and
 * kernel addresses name the low-memory region the kernel owns. */

#define HW_PTR(type, addr) MEM_PTR(volatile type, addr)
#define HW_REF(type, addr) MEM(volatile type, addr)

#define BIOS_KERNEL_BASE   0x80000000u
#define BIOS_EXC_VECTOR    0x80000080u
#define BIOS_BP_VECTOR     0x80000040u
#define BIOS_A0_VECTOR     0x800000A0u
#define BIOS_B0_VECTOR     0x800000B0u
#define BIOS_C0_VECTOR     0x800000C0u
#define BIOS_KERNEL_END    0x8000FFFFu

#endif
