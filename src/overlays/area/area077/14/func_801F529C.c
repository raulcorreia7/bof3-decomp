#include "area077_14.h"

MATCH void func_801F529C(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y) {
    u32  base;
    s32* src;
    s32* dst;
    s32  i;
    s32  temp;

    base = 0x80037800;
    i    = 0;
    dst  = (s32*)((dst_x << 9) + ((dst_y << 5) + base));
    src  = (s32*)((src_x << 9) + ((src_y << 5) + base));
    do {
        temp = *src;
        src += 1;
        i += 1;
        *dst = temp;
        dst += 1;
    } while (i < 8);
    g_GfxPalettePending = 1;
}
