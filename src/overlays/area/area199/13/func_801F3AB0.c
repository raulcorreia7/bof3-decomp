#include "area199_13.h"

#ifdef NON_MATCHING
/* Draws a shaded ring around a screen position. */
NON_MATCHING void func_801F3AB0(s32 x, s32 y, s32 radius, s32 shade) {
    POLY_G4* quad;
    s32      angle;
    s32      next;
    s32      i;

    i = 0;
    do {
        angle = i * 64;
        next  = (i + 1) * 64;
        quad  = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(quad);
        SetSemiTrans(quad, 1);
        setXY4(quad, x + rsin(angle) * (radius + 2) / ONE, y + rcos(angle) * (radius + 2) / ONE, x + rsin(next) * (radius + 2) / ONE, y + rcos(next) * (radius + 2) / ONE,
               x + rsin(angle) * radius / ONE, y + rcos(angle) * radius / ONE, x + rsin(next) * radius / ONE, y + rcos(next) * radius / ONE);
        setRGB0(quad, 0, 0, 0);
        setRGB1(quad, 0, 0, 0);
        setRGB2(quad, shade, shade, shade);
        setRGB3(quad, shade, shade, shade);
        GFX_AddPrim(4, sizeof(POLY_G4));

        quad = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(quad);
        SetSemiTrans(quad, 1);
        setXY4(quad, x + rsin(angle) * radius / ONE, y + rcos(angle) * radius / ONE, x + rsin(next) * radius / ONE, y + rcos(next) * radius / ONE, x + rsin(angle) * (radius - 8) / ONE,
               y + rcos(angle) * (radius - 8) / ONE, x + rsin(next) * (radius - 8) / ONE, y + rcos(next) * (radius - 8) / ONE);
        setRGB0(quad, shade, shade, shade);
        setRGB1(quad, shade, shade, shade);
        setRGB2(quad, 0, 0, 0);
        setRGB3(quad, 0, 0, 0);
        GFX_AddPrim(4, sizeof(POLY_G4));
        i++;
    } while (i < 64);
}
#else
INCLUDE_ASM(func_801F3AB0);
#endif
