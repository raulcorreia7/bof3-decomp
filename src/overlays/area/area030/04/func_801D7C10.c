#include "area030_04.h"

/* Draws the three shop columns from x, lit by the bits of flags (all lit when none is set), and their captions. */
MATCH void func_801D7C10(s32 x, s32 y, s32 flags) {
    u8  slots[3];
    s32 mask;
    s32 i;
    s32 seven;
    u8* strip;
    s16 left;
    s16 top;

    left = x;
    top  = y;
    i    = 0;
    mask = flags & BYTE_MASK;
    for (; i < 3; i++) {
        slots[i] = (mask >> i) & 1;
        func_801D7D68(left + i * 48, top, slots[i]);
        slots[i] += (mask == 0);
    }
    seven = 7;
    strip = &D_801E21C0;
    UI_TextDraw((s16)(left + 6), (s16)(top + 4), (seven - slots[0] * 7) & BYTE_MASK, 4, strip);
    UI_TextDraw((s16)(left + 54), (s16)(top + 4), (seven - slots[1] * 7) & BYTE_MASK, 4, strip + 4);
    UI_TextDraw((s16)(left + 102), (s16)(top + 4), (seven - slots[2] * 7) & BYTE_MASK, 4, strip + 8);
}
