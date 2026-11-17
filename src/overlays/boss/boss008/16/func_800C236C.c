#include "boss008_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C236C(u8 phase) {
    s16      table[64];
    s32      i;
    POLY_G3* prim;

    for (i = 0; i < 64; i++) {
        table[i] = rsin((i * phase) << 6);
    }
    prim = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(prim);
    Area_AddCellPrim(0, 0, 0, sizeof(POLY_G3));
}
#else
INCLUDE_ASM(func_800C236C);
#endif
