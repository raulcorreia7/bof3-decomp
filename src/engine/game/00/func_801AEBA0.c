#include "game_00.h"

MATCH void func_801AEBA0(s16 frame_x, s16 frame_y, s16 frame_width, s16 frame_height, s32 mode_pair_flag) {
    s16 x;
    s16 far_x;
    u16 color;
    u8  r;
    u8  g;
    u8  b;
    u8  mode_a;
    u8  mode_b;

    mode_a = 2;
    if ((mode_pair_flag & 0x1) == 0) {
        mode_a = 1;
    }
    mode_b = 1;
    if ((mode_pair_flag & 0x1) == 0) {
        mode_b = 2;
    }

    x     = frame_x;
    far_x = frame_y + frame_height;

    color = *(u16*)(MEM_PTR(u8, 0x80033A08u) + ((GAME_WINDOW_STYLE << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;

    GFX_DrawLine(x, frame_y, x, far_x - 1, r, g, b, mode_a);
    GFX_DrawLine(x, far_x, x + frame_width - 1, far_x, r, g, b, mode_b);
    GFX_DrawLine(x + frame_width, far_x, x + frame_width, frame_y + 1, r, g, b, mode_b);
    GFX_DrawLine(x + frame_width, frame_y, x + 1, frame_y, r, g, b, mode_a);
}
