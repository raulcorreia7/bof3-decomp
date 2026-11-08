#include "area030_04.h"

/* Draws the three shop panel columns selected by the low three bits
 * of arg2 at screen columns arg0 + 0x00/0x30/0x60 and row arg1 + 4: each
 * column is drawn by func_801D7D68 and its icon strip painted through
 * func_8014F800. */
/* nonmatching 73.03%: retail keeps y in s4 and narrows it directly in a1; this source uses
 * a separate saved temporary and stores the slot byte before the call instead of in its delay slot.
 * resume: align the live ranges and defer the slot store. */
/* Indexed slots with an unconditional increment match the tail; pointer hoisting first differs at +0x14. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D7C10(s32 arg0, s32 arg1, s32 arg2) {
    u8  slots[3];
    u8* slot;
    s32 x;
    s32 mask;
    s32 i;
    s32 seven;
    u8* strip;

    mask = arg2 & BYTE_MASK;
    x    = arg0;
    for (i = 0; i < 3; i++, x += 48) {
        slot  = &slots[i];
        *slot = (mask >> i) & 1;
        func_801D7D68(x, arg1, *slot);
        if (mask == 0) {
            *slot += 1;
        }
    }
    seven = 7;
    strip = &D_801E21C0;
    UI_DrawText((s16)(arg0 + 6), (s16)(arg1 + 4), (seven - slots[0] * 7) & BYTE_MASK, 4, strip);
    UI_DrawText((s16)(arg0 + 54), (s16)(arg1 + 4), (seven - slots[1] * 7) & BYTE_MASK, 4, (strip + 4));
    UI_DrawText((s16)(arg0 + 102), (s16)(arg1 + 4), (seven - slots[2] * 7) & BYTE_MASK, 4, (strip + 8));
}
#else
INCLUDE_ASM(func_801D7C10);
#endif
