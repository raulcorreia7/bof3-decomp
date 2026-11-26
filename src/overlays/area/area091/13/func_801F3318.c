#include "area091_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3318(void) {
    u16* colors;
    u16  color_a;
    u16  color_b;
    u8   index;
    u32  arena;
    u32  work;

    SELF(Actor)->unk_0A--;
    if (SELF(Actor)->unk_0A != 0) {
        arena   = AREA_PALETTE_ARENA;
        colors  = MEM_PTR(u16, arena + (SELF(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (SELF(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        index   = SELF(Actor)->param.unk_0B;
        color_a = (colors[index] & 0x7BDE) >> 1;
        color_b = (colors[31 - index] & 0x7BDE) >> 1;
    } else {
        arena   = AREA_PALETTE_ARENA;
        colors  = MEM_PTR(u16, arena + (SELF(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (SELF(Actor)->clut_select & 7) * AREA_PALETTE_UNIT);
        index   = SELF(Actor)->param.unk_0B;
        color_a = colors[index];
        color_b = colors[31 - index];
    }
    work                                                                                                                                                         = AREA_PALETTE_WORK;
    MEM_PTR(u16, work + (SELF(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (SELF(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[SELF(Actor)->param.unk_0B]      = color_a;
    MEM_PTR(u16, work + (SELF(Actor)->clut_select >> 3) * AREA_PALETTE_ROW + (SELF(Actor)->clut_select & 7) * AREA_PALETTE_UNIT)[31 - SELF(Actor)->param.unk_0B] = color_b;
    if (SELF(Actor)->unk_0A == 0) {
        SELF(Actor)->unk_0A = 2;
        SELF(Actor)->param.unk_0B++;
        if (SELF(Actor)->param.unk_0B == 0x10) {
            SELF(Actor)->unk_0A = 0x1E;
            SELF(Actor)->unk_04++;
        }
    }
    g_GfxPalettePending++;
    func_801F2ED4(300, 0xFF);
}
#else
INCLUDE_ASM(func_801F3318);
#endif
