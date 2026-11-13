#include "area048_13.h"

MATCH void func_801F3274(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    AREA_DRAW_TRIANGLE_FAN(x, y, radius, angle, D_801F4D5C, D_801F4D5D, D_801F4D5E);
}
