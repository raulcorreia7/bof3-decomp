#include "area077_14.h"

MATCH void func_801F529C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32  base;
    s32* src;
    s32* dst;
    s32  i;
    s32  temp;

    base = 0x80037800;
    i    = 0;
    dst  = (s32*)((arg2 << 9) + ((arg3 << 5) + base));
    src  = (s32*)((arg0 << 9) + ((arg1 << 5) + base));
    do {
        temp = *src;
        src += 1;
        i += 1;
        *dst = temp;
        dst += 1;
    } while (i < 8);
    g_GfxPalettePending = 1;
}
