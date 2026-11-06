#include "battle_03.h"

MATCH void func_801DA408(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b) {
    LINE_F2* primitive;

    primitive = (LINE_F2*)BATTLE_GLOBAL_WORD_598C;
    SetLineF2(primitive);
    setRGB0(primitive, r, g, b);
    setXY2(primitive, x0, y0, x1, y1);
    GFX_AddPrim(1u, 0x10u);
}
