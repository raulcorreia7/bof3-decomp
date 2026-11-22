#include "engine/game/00/game_00.h"

/* Draws the four edges and the cut corners of the rectangle at (x, y) in the colour row of the window
 * style; the high nibble of the flag byte cuts the corners. */
#ifdef NON_MATCHING
NON_MATCHING void UI_WindowDrawOutline(s16 x, s16 y, s16 width, s32 height, s32 flags) {
    u16 corner[4];
    u16 color;
    s32 left;
    s32 top;
    s32 x_end;
    s16 y_end;
    s16 edge;
    s32 mode_flag;
    s32 mode_arg;
    u8  r;
    u8  g;
    u8  b;
    u8  mode_a;
    u8  mode_b;
    s32 i;
    s32 bit;
    s32 index;

    mode_a    = 2;
    left      = x;
    top       = y;
    x_end     = width;
    color     = *(u16*)((u8*)D_80033A08 + ((GAME_WINDOW_STYLE << 6) | 0x20));
    mode_flag = flags & 1;
    if (mode_flag == 0) {
        mode_a = 1;
    }
    mode_b = 1;
    if (mode_flag == 0) {
        mode_b = 2;
    }
    bit = 1;
    i   = 0;
    do {
        index = i & BYTE_MASK;
        if (bit & ((flags & BYTE_MASK) >> 4)) {
            corner[index] = 3;
        } else {
            corner[index] = 0;
        }
        i++;
        bit *= 2;
    } while ((i & BYTE_MASK) < 4U);
    r        = PSX_COLOR_R(color) << 3;
    g        = PSX_COLOR_G(color) << 3;
    b        = PSX_COLOR_B(color) << 3;
    mode_arg = mode_a;
    y_end    = top + height;

    GFX_DrawLine(left, top + corner[0], left, y_end - (corner[2] + 1), r, g, b, mode_arg);
    if ((s16)corner[0] != 0) {
        GFX_DrawLine(left, y_end - (corner[2] + 1), left + corner[2], y_end, r, g, b, mode_b);
    }
    edge = y_end;
    x_end += left;
    GFX_DrawLine(left + corner[2], edge, x_end - (corner[3] + 1), edge, r, g, b, mode_b);
    if ((s16)corner[1] != 0) {
        GFX_DrawLine(x_end - (corner[3] + 1), edge, x_end, y_end - corner[3], r, g, b, mode_b);
    }
    edge = x_end;
    GFX_DrawLine(edge, y_end - corner[3], edge, top + corner[1] + 1, r, g, b, mode_b);
    if ((s16)corner[2] != 0) {
        GFX_DrawLine(edge, top + corner[1] + 1, x_end - corner[1], top, r, g, b, mode_arg);
    }
    edge = top;
    GFX_DrawLine(x_end - corner[1], edge, left + corner[0] + 1, edge, r, g, b, mode_arg);
    if ((s16)corner[3] != 0) {
        GFX_DrawLine(left + corner[0] + 1, edge, left, top + corner[0], r, g, b, mode_arg);
    }
}
#else
INCLUDE_ASM(UI_WindowDrawOutline);
#endif
