#define FAKE_DECL_TASK_VOLATILE
#include "area042_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3280(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* prim;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(prim, D_801F52C4[3 * g_Task->unk_06], D_801F52C5[3 * g_Task->unk_06], D_801F52C6[3 * g_Task->unk_06]);
    setRGB1(prim, D_801F52C4[3 * g_Task->unk_06], D_801F52C5[3 * g_Task->unk_06], D_801F52C6[3 * g_Task->unk_06]);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(3, sizeof(POLY_G4));

    prim += 1;
    prim[0]  = prim[-1];
    prim->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    prim->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    prim->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    prim->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    GFX_AddPrim(3, sizeof(POLY_G4));
}
#else
INCLUDE_ASM(func_801F3280);
#endif
