#include "engine/slus/slus.h"

/* The kernel's low-memory block starts at 0x100: its exception handler
 * (func_8017A328) reads the +0x08 pointer from it, and the word at +0x10 is the
 * base of a run of 0xC0-byte work blocks. Holding that base in a local is what
 * leaves 0x10 as the load displacement (the retail shape); a folded constant
 * address does not match. */

/* seeds the four callback scheduler slots: each starts empty with work block i + 1 of the kernel run at
 * +0x0C (its +0x94 word pinned to 0x40000404) and the thread stack 0x801FF400 + 0x200 * (i + 1) at +0x10.
 */
MATCH void CallbackInitThreads(void) {
    s32 i;
    s32 slot_offset;
    s32 block_offset;
    u8* kernel;

    kernel = KERNEL_RAM(0u);
    for (i = 0; i < 4; i++) {
        slot_offset                                                    = i << 7;
        /* Product-then-bias keeps the multiply on the pre-increment counter, as
         * retail does; a (i + 1) * 0xC0 spelling moves it onto the incremented
         * counter. */
        block_offset                                                   = i * 0xC0 + 0xC0;
        *(u16*)((u8*)D_80143B40 + slot_offset)                         = 0;
        *(s32*)((u8*)&D_80143B4C + slot_offset)                        = *(u32*)(kernel + 0x10) + block_offset;
        *(s32*)((u8*)&D_80143B50 + slot_offset)                        = 0x801FF400 + (i + 1) * 0x200;
        *(s32*)((u8*)(*(s32*)((u8*)&D_80143B4C + slot_offset)) + 0x94) = 0x40000404;
    }
}
