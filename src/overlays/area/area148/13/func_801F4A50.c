#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4A50(s16 x0, s16 y0, s16 radius0, u16 angle0, s16 x1, s16 y1, s16 radius1, u16 angle1) {
    POLY_G4* poly;
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x0, y0, x1, y1, x0 + FIXED_MUL(radius0, rcos(angle0)), y0 + FIXED_MUL(radius0, rsin(angle0)), x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180)),
           y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180)));
    setRGB0(poly, 64, 0, 0);
    setRGB1(poly, 64, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x1 = x0 + FIXED_MUL(radius0, rcos(angle0 + ANGLE_180));
    poly->y1 = y0 + FIXED_MUL(radius0, rsin(angle0 + ANGLE_180));
    poly->x3 = x1 + FIXED_MUL(radius1, rcos(angle1));
    poly->y3 = y1 + FIXED_MUL(radius1, rsin(angle1));
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));
}
#else
INCLUDE_ASM(func_801F4A50);
#endif
