#include "engine/game/00/game_00.h"

/* Draws the four edges and the cut corners of the rectangle at (x, y) in the colour row of the window
 * style; the high nibble of the flag byte cuts the corners. */
#ifdef NON_MATCHING
NON_MATCHING void UI_WindowDrawOutline(s32 x, s32 y, s32 width, s32 height, s32 flags) {
    u16 corner[4];
    s16 left;
    u16 color;
    s32 bottom;
    s32 right;
    s32 mode_flag;
    u8  r;
    u8  g;
    u8  b;
    s32 mode_a;
    u8  mode_b;
    s32 i;
    s32 bit;
    s32 index;

    mode_a    = 2;
    left      = x;
    color     = *(u16*)((u8*)D_80033A08 + ((GAME_WINDOW_STYLE << 6) | 0x20));
    r         = PSX_COLOR_R(color) << 3;
    g         = PSX_COLOR_G(color) << 3;
    b         = PSX_COLOR_B(color) << 3;
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
        if (bit & ((u8)flags >> 4)) {
            corner[index] = 3;
        } else {
            corner[index] = 0;
        }
        i++;
        bit *= 2;
    } while ((i & BYTE_MASK) < 4U);
    bottom = y + height;
    GFX_DrawLine(left, y + corner[0], left, bottom - (corner[2] + 1), r, g, b, mode_a);
    if ((s16)corner[0] != 0) {
        GFX_DrawLine(left, bottom - (corner[2] + 1), x + corner[2], bottom, r, g, b, mode_b);
    }
    right = x + width;
    GFX_DrawLine(x + corner[2], bottom, right - (corner[3] + 1), bottom, r, g, b, mode_b);
    if ((s16)corner[1] != 0) {
        GFX_DrawLine(right - (corner[3] + 1), bottom, right, bottom - corner[3], r, g, b, mode_b);
    }
    GFX_DrawLine(right, bottom - corner[3], right, y + (corner[1] + 1), r, g, b, mode_b);
    if ((s16)corner[2] != 0) {
        GFX_DrawLine(right, y + (corner[1] + 1), right - corner[1], y, r, g, b, mode_a);
    }
    GFX_DrawLine(right - corner[1], y, x + (corner[0] + 1), y, r, g, b, mode_a);
    if ((s16)corner[3] != 0) {
        GFX_DrawLine(x + (corner[0] + 1), y, left, y + corner[0], r, g, b, mode_a);
    }
}
#else
INCLUDE_ASM(UI_WindowDrawOutline);
#endif
