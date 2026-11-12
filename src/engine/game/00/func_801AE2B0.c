#include "game_00.h"

MATCH void func_801AE2B0(s16 quad_x, s16 quad_y, s32 quad_width, s32 quad_height, u8 use_frame_shade) {
    POLY_F4* prim;
    u32      shade;
    s16      x;
    s16      y;
    s32      width;
    s32      height;
    s32      width_plus_1;
    s32      height_plus_1;

    x      = quad_x;
    y      = quad_y;
    width  = quad_width;
    height = quad_height;
    if (use_frame_shade != 0) {
        shade = (((g_FrameCount & 0x8) ? (g_FrameCount & 0x6) : (~g_FrameCount & 0x6)) << 5) | 0x3F;
    } else {
        shade = 0xFF;
    }
    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setRGB0(prim, shade, shade, 0);
    setXY0(prim, x, y);
    width_plus_1  = (width & BYTE_MASK) + 1;
    prim->x1      = width_plus_1 + x;
    prim->y1      = y;
    prim->x2      = x;
    height_plus_1 = (height & BYTE_MASK) + 1;
    prim->y2      = height_plus_1 + y;
    prim->x3      = width_plus_1 + x;
    prim->y3      = height_plus_1 + y;
    GFX_AddPrim(1, sizeof(POLY_F4));
}
