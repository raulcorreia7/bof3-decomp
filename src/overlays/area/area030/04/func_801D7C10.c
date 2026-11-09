#include "area030_04.h"

/* Draws the three shop panel columns selected by the low three bits of mask at screen columns x + 0x00/0x30/0x60 and row y + 4. */
/* nonmatching 73.03%: retail keeps y in s4 and narrows it directly in a1; this source uses
 * a separate saved temporary and stores the slot byte before the call instead of in its delay slot.
 * resume: align the live ranges and defer the slot store. */
/* Indexed slots with an unconditional increment match the tail; pointer hoisting first differs at +0x14. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D7C10(s32 x, s32 y, s32 flags) {
    u8  slots[3];
    u8* slot;
    s32 base_x;
    s32 mask;
    s32 i;
    s32 seven;
    u8* strip;

    mask   = flags & BYTE_MASK;
    base_x = x;
    for (i = 0; i < 3; i++, base_x += 48) {
        slot  = &slots[i];
        *slot = (mask >> i) & 1;
        func_801D7D68(base_x, y, *slot);
        if (mask == 0) {
            *slot += 1;
        }
    }
    seven = 7;
    strip = &D_801E21C0;
    UI_DrawText((s16)(x + 6), (s16)(y + 4), (seven - slots[0] * 7) & BYTE_MASK, 4, strip);
    UI_DrawText((s16)(x + 54), (s16)(y + 4), (seven - slots[1] * 7) & BYTE_MASK, 4, (strip + 4));
    UI_DrawText((s16)(x + 102), (s16)(y + 4), (seven - slots[2] * 7) & BYTE_MASK, 4, (strip + 8));
}
#else
INCLUDE_ASM(func_801D7C10);
#endif
