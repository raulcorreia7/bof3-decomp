#include "area199_13.h"

MATCH void func_801F3EA0(s32 x, s32 y, s32 radius, u8 shade) {
    POLY_G3* prim;
    s32      i;

    i = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, x, y, x + rsin(i << 6) * radius / ONE, y + rcos(i << 6) * radius / ONE, x + rsin((i + 1) << 6) * radius / ONE, y + rcos((i + 1) << 6) * radius / ONE);
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        GFX_AddPrim(4, sizeof(POLY_G3));
        i++;
    } while (i < AREA_SHADE_FAN_SEGMENTS);
}
