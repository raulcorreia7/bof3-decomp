#include "area067_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F38A0(s16* row) {
    POLY_F4* prim;
    s16      top;
    s16      bottom;

    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 0);
    top      = (u16)row[1] - (u16)row[2];
    prim->y0 = prim->y1 = top;
    if (top < row[4]) {
        prim->y0 = prim->y1 = row[4];
    }
    bottom   = (u16)row[1] + (u16)row[2];
    prim->y2 = prim->y3 = bottom;
    if (bottom > (s16)row[5]) {
        prim->y2 = prim->y3 = row[5];
    }
    prim->x0 = prim->x2 = (u16)row[0];
    prim->x1 = prim->x3 = (u16)row[0] + 2;
    setRGB0(prim, 0x80, 0x80, 0x80);
    /* FAKE: the barrier keeps the depth constant out of the branch delay slot, as retail leaves it. */
    FAKE_BARRIER();
    Area_CellAddPrim(D_801F53A0, D_801F53A4, 4, sizeof(POLY_F4));
}
#else
INCLUDE_ASM(func_801F38A0);
#endif
