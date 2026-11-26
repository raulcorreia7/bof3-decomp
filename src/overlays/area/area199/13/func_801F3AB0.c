#include "area199_13.h"

/* Draws a shaded ring around a screen position. */
MATCH void func_801F3AB0(s32 x, s32 y, s32 radius, s32 shade) {
    POLY_G4* quad;
    s32      i;

    i = 0;
    do {
        quad = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(quad);
        SetSemiTrans(quad, 1);
        setXY4(quad, x + rsin(i * 64) * (radius + 2) / ONE, y + rcos(i * 64) * (radius + 2) / ONE, x + rsin((i + 1) * 64) * (radius + 2) / ONE, y + rcos((i + 1) * 64) * (radius + 2) / ONE,
               x + rsin(i * 64) * radius / ONE, y + rcos(i * 64) * radius / ONE, x + rsin((i + 1) * 64) * radius / ONE, y + rcos((i + 1) * 64) * radius / ONE);
        setRGB0(quad, 0, 0, 0);
        setRGB1(quad, 0, 0, 0);
        setRGB2(quad, shade, shade, shade);
        setRGB3(quad, shade, shade, shade);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_G4));

        quad = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(quad);
        SetSemiTrans(quad, 1);
        setXY4(quad, x + rsin(i * 64) * radius / ONE, y + rcos(i * 64) * radius / ONE, x + rsin((i + 1) * 64) * radius / ONE, y + rcos((i + 1) * 64) * radius / ONE,
               x + rsin(i * 64) * (radius - 8) / ONE, y + rcos(i * 64) * (radius - 8) / ONE, x + rsin((i + 1) * 64) * (radius - 8) / ONE, y + rcos((i + 1) * 64) * (radius - 8) / ONE);
        setRGB0(quad, shade, shade, shade);
        setRGB1(quad, shade, shade, shade);
        setRGB2(quad, 0, 0, 0);
        setRGB3(quad, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_G4));
        i++;
    } while (i < 64);
}
