#include "area085_13.h"

MATCH void func_801F3C3C(s32 delta) {
    u16* src;
    u16* dst;
    u16  color;
    s32  r;
    s32  g;
    s32  b;

    dst = (u16*)0x80038400;
    src = (u16*)0x80034400;
    do {
        color = *src;
        r     = color & 0x1F;
        g     = (color >> 5) & 0x1F;
        b     = (color >> 10) & 0x1F;
        if (r != 0) {
            r += delta;
            if (r <= 0) {
                r = 0;
            }
            if (!(r < 0x20)) {
                r = 0x1F;
            }
        }
        if (g != 0) {
            g += delta;
            if (g <= 0) {
                g = 0;
            }
            if (!(g < 0x20)) {
                g = 0x1F;
            }
        }
        if (b != 0) {
            b += delta;
            if (b <= 0) {
                b = 0;
            }
            if (!(b < 0x20)) {
                b = 0x1F;
            }
        }
        *dst = (*src & 0x8000) | (b << 0xA) | (g << 5) | r;
        dst += 1;
        src += 1;
    } while ((s32)dst < (s32)0x80038600);
    g_GfxPalettePending = 1;
}
