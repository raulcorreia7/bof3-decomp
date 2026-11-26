#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4DF0(s32 x, s32 y, s16 radius, u16 angle) {
    /* FAKE: retail reserves 0x10 unused frame bytes. */
    FAKE_STACK_PADS(u8, 0x10);

    POLY_G3* prim;
    s32      i;

    i = 0;
    do {
        prim = GFX_BeginPolyG3(1);
        setXY2(prim, x, y, x + FIXED_MUL(radius, rcos(angle)), y + FIXED_MUL(radius, rsin(angle)));
        angle += ANGLE_45 / 2;
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));
        setRGB0(prim, D_801F6138[SELF(Actor)->unk_06][0], D_801F6138[SELF(Actor)->unk_06][1], D_801F6138[SELF(Actor)->unk_06][2]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        Area_CellAddPrim(SELF(Actor)->unk_18, SELF(Actor)->unk_1C, 0, sizeof(POLY_G3));
    } while (i < 8);
}
#else
INCLUDE_ASM(func_801F4DF0);
#endif
