#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F656C(void) {
    /* FAKE: retail keeps the grid pointer in s3; the best pure-C body puts it in s4. */
    FAKE_REG(u8*, base, "s3");
    s32 col;
    s32 row;
    s16 y;
    s32 x;
    s32 v;
    u8  index;
    u8  pending;
    u8  next;
    /* FAKE: retail reserves 8 bytes of frame that no statement uses. */
    FAKE_STACK_PADS(u8, 8);

    MEM(u16, AREA_CODE_BASE)     = 20;
    MEM(u16, AREA_CODE_BASE + 2) = 68;
    base                         = MEM_PTR(u8, AREA_CODE_BASE + 4);
    row                          = 13;
    do {
        col = 5;
        y   = row;
        x   = 0x60000;
        do {
            v     = func_801F66D0(col, y);
            *base = v | (func_801F66D0(x >> 16, y) << 4);
            x += 0x20000;
            col += 2;
            base++;
        } while (col < 0x55);
        row++;
    } while (row < 0x52);
    index                = D_80145A00;
    next                 = index + 1;
    pending              = g_GfxPalettePending + 1;
    D_80145A54[index]    = 0x380;
    (&D_80145A7C)[index] = 0x100;
    (&D_80145A04)[index] = AREA_CODE_BASE;
    D_800396C0[0]        = 0xFE10;
    D_800396C0[1]        = 0xDC00;
    D_800396C0[2]        = 0x8908;
    D_80145A00           = next;
    D_800396C0[3]        = 0x85F;
    g_GfxPalettePending  = pending;
}
#else
INCLUDE_ASM(func_801F656C);
#endif
