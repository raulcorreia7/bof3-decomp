#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4A50(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* poly;

    /* FAKE: retail reserves 0x20 frame bytes above the parameter homes that no access explains. */
    FAKE_STACK_PADS(u8, 0x20);

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(poly, D_801F6138[SELF(Actor)->unk_06][0], D_801F6138[SELF(Actor)->unk_06][1], D_801F6138[SELF(Actor)->unk_06][2]);
    setRGB1(poly, D_801F6138[SELF(Actor)->unk_06][0], D_801F6138[SELF(Actor)->unk_06][1], D_801F6138[SELF(Actor)->unk_06][2]);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    poly->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    poly->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    poly->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(POLY_G4));
}
#else
INCLUDE_ASM(func_801F4A50);
#endif
