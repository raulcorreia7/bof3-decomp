#include "area077_14.h"

/* Draws the village panel at (x, y): the two blended fills, the raised and lowered edge rows, the
 * eight-pixel grid with the bright centre row, and the tinted marks; then the actor tint steps down. */
MATCH void func_801F31EC(s16 x, s16 y) {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
    s16 inner_left;
    s16 inner_top;
    s16 inner_right;
    s16 inner_bottom;
    s16 step;
    s16 r;
    s16 g;
    u8  tint;

    left   = x;
    top    = y;
    right  = x + 0x47;
    bottom = y + 0x47;
    GFX_AddBlendDrawMode(2);
    D_801F6B74 = 0x40;
    D_801F6B70 = 0x40;
    D_801F6B6C = 0x40;
    func_801F3BC4(x, y, 0x48, 0x48);
    GFX_AddBlendDrawMode(1);
    D_801F6B70 = 0x40;
    D_801F6B74 = 0;
    D_801F6B6C = 0;
    func_801F3BC4(x, y, 0x48, 0x48);
    GFX_AddBlendDrawMode(1);
    D_801F6B70   = 0x40;
    D_801F6B74   = 0;
    D_801F6B6C   = 0;
    inner_left   = x + 3;
    inner_bottom = y + 0x44;
    inner_right  = x + 0x44;
    inner_top    = y + 3;
    func_801F30E8(left, top, right, top);
    func_801F30E8(left, top, left, bottom);
    func_801F30E8(inner_left, inner_bottom, inner_right, inner_bottom);
    func_801F30E8(inner_right, inner_top, inner_right, inner_bottom);
    GFX_AddBlendDrawMode(2);
    func_801F30E8(left, bottom, right, bottom);
    func_801F30E8(right, top, right, bottom);
    func_801F30E8(inner_left, inner_top, inner_right, inner_top);
    func_801F30E8(inner_left, inner_top, inner_left, inner_bottom);
    GFX_AddBlendDrawMode(1);
    for (step = 0xC; step < 0x44; step += 8) {
        if (step == 0x24) {
            r = 0x40;
            g = 0;
        } else {
            r = 0;
            g = 0x40;
        }
        D_801F6B6C = 0;
        D_801F6B70 = 0x40;
        func_801F30E8(x + 4, y + step, x + 0x44, y + step);
        D_801F6B6C = r;
        D_801F6B70 = g;
        func_801F30E8(x + step, y + 4, x + step, y + 0x44);
    }
    D_801F6B6C = 0x80;
    tint       = TASK(Actor)->tint.bytes.rgb.r;
    D_801F6B74 = tint;
    D_801F6B70 = tint;
    func_801F30E8(x + 4, y + 0x24, x + 0xA, y + 0x24);
    func_801F30E8(x + 0x3E, y + 0x24, x + 0x44, y + 0x24);
    func_801F30E8(x + 0x21, y + 0xC, x + 0x27, y + 0xC);
    func_801F30E8(x + 0x21, y + 0x3C, x + 0x27, y + 0x3C);
    if (TASK(Actor)->tint.bytes.rgb.r != 0) {
        TASK(Actor)->tint.bytes.rgb.r -= 0x10;
    }
}
