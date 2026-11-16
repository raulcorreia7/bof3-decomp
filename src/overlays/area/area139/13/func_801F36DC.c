#include "area139_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F36DC(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* poly;

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(poly, D_801F442C[g_Task->unk_06 * 3], D_801F442D[g_Task->unk_06 * 3], D_801F442E[g_Task->unk_06 * 3]);
    setRGB1(poly, D_801F442C[g_Task->unk_06 * 3], D_801F442D[g_Task->unk_06 * 3], D_801F442E[g_Task->unk_06 * 3]);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    poly->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    poly->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    poly->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_G4));
}
#else
INCLUDE_ASM(func_801F36DC);
#endif
