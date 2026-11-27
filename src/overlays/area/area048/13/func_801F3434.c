#include "area048_13.h"

/* Draws the two-quad ring segment between two circles in the task colour row. */
MATCH void func_801F3434(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* prim;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(prim, D_801F4D5C[SELF(Actor)->unk_06 * 3], D_801F4D5D[SELF(Actor)->unk_06 * 3], D_801F4D5E[SELF(Actor)->unk_06 * 3]);
    setRGB1(prim, D_801F4D5C[(s16)(SELF(Actor)->unk_06 * 3)], D_801F4D5D[(s16)(SELF(Actor)->unk_06 * 3)], D_801F4D5E[(s16)(SELF(Actor)->unk_06 * 3)]);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));
    prim++;
    memcpy(prim, prim - 1, sizeof(POLY_G4));
    prim->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    prim->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    prim->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    prim->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));
}
