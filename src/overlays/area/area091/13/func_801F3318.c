#include "area091_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3318(void) {
    u16* src;
    u16  color_a;
    u16  color_b;
    u8   index;
    u32  work;

    work = AREA_PALETTE_WORK;
    TASK(Actor)->unk_0A--;
    if (TASK(Actor)->unk_0A != 0) {
        index   = TASK(Actor)->param.unk_0B;
        src     = MEM_PTR(u16, AREA_PALETTE_ARENA + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        color_a = (src[index] & 0x7BDE) >> 1;
        color_b = (src[31 - index] & 0x7BDE) >> 1;
    } else {
        index   = TASK(Actor)->param.unk_0B;
        src     = MEM_PTR(u16, AREA_PALETTE_ARENA + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        color_a = src[index];
        color_b = src[31 - index];
    }
    MEM_PTR(u16, work + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[index]      = color_a;
    MEM_PTR(u16, work + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[31 - index] = color_b;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->unk_0A = 2;
        if (++TASK(Actor)->param.unk_0B == 0x10) {
            TASK(Actor)->unk_0A = 0x1E;
            TASK(Actor)->unk_04++;
        }
    }
    g_GfxPalettePending++;
    func_801F2ED4(300, 0xFF);
}
#else
INCLUDE_ASM(func_801F3318);
#endif
