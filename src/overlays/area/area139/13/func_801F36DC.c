#include "area139_13.h"

/* Draws the two-quad ring segment between two circles in the task colour row. */
MATCH void func_801F36DC(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* poly;

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(poly, D_801F442C[SELF(Actor)->unk_06 * 3], D_801F442D[SELF(Actor)->unk_06 * 3], D_801F442E[SELF(Actor)->unk_06 * 3]);
    setRGB1(poly, D_801F442C[(s16)(SELF(Actor)->unk_06 * 3)], D_801F442D[(s16)(SELF(Actor)->unk_06 * 3)], D_801F442E[(s16)(SELF(Actor)->unk_06 * 3)]);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    poly->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    poly->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    poly->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_G4));
}
