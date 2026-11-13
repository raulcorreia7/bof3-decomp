#include "area042_13.h"

MATCH void func_801F30C0(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    AREA_DRAW_TRIANGLE_FAN(x, y, radius, angle, D_801F52C4, D_801F52C5, D_801F52C6);
}
