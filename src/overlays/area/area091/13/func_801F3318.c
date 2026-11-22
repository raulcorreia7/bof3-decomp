#include "area091_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3318(void) {
    u16* colors;
    u16  color_a;
    u16  color_b;
    u8   index;
    u32  arena;
    u32  work;

    TASK(Actor)->unk_0A--;
    if (TASK(Actor)->unk_0A != 0) {
        arena   = AREA_PALETTE_ARENA;
        colors  = MEM_PTR(u16, arena + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        index   = TASK(Actor)->param.unk_0B;
        color_a = (colors[index] & 0x7BDE) >> 1;
        color_b = (colors[31 - index] & 0x7BDE) >> 1;
    } else {
        arena   = AREA_PALETTE_ARENA;
        colors  = MEM_PTR(u16, arena + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        index   = TASK(Actor)->param.unk_0B;
        color_a = colors[index];
        color_b = colors[31 - index];
    }
    work                                                                                                                                                         = AREA_PALETTE_WORK;
    MEM_PTR(u16, work + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[TASK(Actor)->param.unk_0B]      = color_a;
    MEM_PTR(u16, work + (TASK(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (TASK(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[31 - TASK(Actor)->param.unk_0B] = color_b;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->unk_0A = 2;
        TASK(Actor)->param.unk_0B++;
        if (TASK(Actor)->param.unk_0B == 0x10) {
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
