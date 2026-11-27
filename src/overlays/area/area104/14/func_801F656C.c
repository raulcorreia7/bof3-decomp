#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F656C(void) {
    u8* base;
    s32 col;
    s32 row;
    s16 y;
    s32 v;
    u8  index;
    u8  pending;
    u8  next;

    base                         = MEM_PTR(u8, AREA_CODE_BASE + 4);
    row                          = 13;
    MEM(u16, AREA_CODE_BASE)     = 20;
    MEM(u16, AREA_CODE_BASE + 2) = 68;
    do {
        col = 5;
        y   = row;
        do {
            v     = func_801F66D0(col, y);
            *base = v | (func_801F66D0(col + 1, y) << 4);
            col += 2;
            base++;
        } while (col < 0x55);
        row++;
    } while (row < 0x52);
    index                  = g_GfxTransferCount;
    next                   = index + 1;
    pending                = g_GfxPalettePending + 1;
    D_80145A54[index]      = 0x380;
    D_80145A54[index + 20] = 0x100;
    (&D_80145A04)[index]   = AREA_CODE_BASE;
    D_800396C0[0]          = 0xFE10;
    D_800396C0[1]          = 0xDC00;
    D_800396C0[2]          = 0x8908;
    g_GfxTransferCount     = next;
    D_800396C0[3]          = 0x85F;
    g_GfxPalettePending    = pending;
}
#else
INCLUDE_ASM(func_801F656C);
#endif
