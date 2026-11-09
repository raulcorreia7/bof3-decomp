#include "engine/slus/slus.h"

/* The kernel's low-memory block starts at 0x100. */

/* seeds the four callback scheduler slots. */
MATCH void CallbackInitThreads(void) {
    s32 i;
    s32 slot_offset;
    s32 block_offset;
    u8* kernel;

    kernel = KERNEL_RAM(0u);
    for (i = 0; i < 4; i++) {
        slot_offset                                               = i << 7;
        /* Product-then-bias keeps the multiply on the pre-increment counter, as retail does. */
        block_offset                                              = i * 0xC0 + 0xC0;
        FIELD(u16, D_80143B40, slot_offset)                       = 0;
        FIELD(s32, &D_80143B4C, slot_offset)                      = *(u32*)(kernel + 0x10) + block_offset;
        FIELD(s32, &D_80143B50, slot_offset)                      = 0x801FF400 + (i + 1) * 0x200;
        *(s32*)((u8*)FIELD(s32, &D_80143B4C, slot_offset) + 0x94) = 0x40000404;
    }
}
