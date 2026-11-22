#include "area030_04.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D7C10(s32 x, s32 y, s32 flags) {
    u8  slots[3];
    s32 base_x;
    s32 mask;
    s32 i;
    s32 seven;
    u8* strip;

    mask   = flags & BYTE_MASK;
    base_x = x;
    for (i = 0; i < 3; i++, base_x += 48) {
        slots[i] = (mask >> i) & 1;
        func_801D7D68(base_x, y, slots[i]);
        slots[i] += (mask == 0);
    }
    seven = 7;
    strip = &D_801E21C0;
    UI_TextDraw((s16)(x + 6), (s16)(y + 4), (seven - slots[0] * 7) & BYTE_MASK, 4, strip);
    UI_TextDraw((s16)(x + 54), (s16)(y + 4), (seven - slots[1] * 7) & BYTE_MASK, 4, strip + 4);
    UI_TextDraw((s16)(x + 102), (s16)(y + 4), (seven - slots[2] * 7) & BYTE_MASK, 4, strip + 8);
}
#else
INCLUDE_ASM(func_801D7C10);
#endif
