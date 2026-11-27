#include "area168_13.h"

/* Draws the two-quad ring segment between two circles in the task colour row. */
MATCH void func_801F3040(s16 x0, s16 y0, s16 radius0, u16 angle0, s16 x1, s16 y1, s16 radius1, u16 angle1) {
    POLY_G4* prim;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x0, y0, x1, y1, x0 + FIXED_MUL(radius0, rcos(angle0)), y0 + FIXED_MUL(radius0, rsin(angle0)), x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180)),
           y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180)));
    setRGB0(prim, D_801F4B2C[SELF(Actor)->unk_06 * 3], D_801F4B2D[SELF(Actor)->unk_06 * 3], D_801F4B2E[SELF(Actor)->unk_06 * 3]);
    setRGB1(prim, D_801F4B2C[(s16)(SELF(Actor)->unk_06 * 3)], D_801F4B2D[(s16)(SELF(Actor)->unk_06 * 3)], D_801F4B2E[(s16)(SELF(Actor)->unk_06 * 3)]);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, 0, 0, 0);
    Area_CellAddPrim(SELF(Actor)->vx, SELF(Actor)->vy, 1, sizeof(POLY_G4));
    prim++;
    memcpy(prim, prim - 1, sizeof(POLY_G4));
    prim->x2 = x0 + FIXED_MUL(radius0, rcos(angle0 + ANGLE_180));
    prim->y2 = y0 + FIXED_MUL(radius0, rsin(angle0 + ANGLE_180));
    prim->x3 = x1 + FIXED_MUL(radius1, rcos(angle1));
    prim->y3 = y1 + FIXED_MUL(radius1, rsin(angle1));
    Area_CellAddPrim(SELF(Actor)->vx, SELF(Actor)->vy, 1, sizeof(POLY_G4));
}
