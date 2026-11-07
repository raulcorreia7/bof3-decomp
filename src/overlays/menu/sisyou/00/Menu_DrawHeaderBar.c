#include "sisyou_00.h"

/* nonmatching 60.2%: tried raw byte-offset spelling of both texture_window increments (60.18%, no change); frame-slot
 * delta 0x78 vs 0x70 with identical save set. resume: when a source shape forces all four args to home (retail sw
 * a0..a3 at 0x18/0x20/0x28/0x30, 8-byte-spaced, with lhu reloads of x/y from the homes) instead of keeping x/y in
 * callee-saved registers; then re-measure the five opcode and three branch hunks. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s16       left;
    s16       new_var;
    s16       top;
    s16       x_inner;
    s32       clut_x;
    s16       bottom_y;
    u8        bottom_v;
    s32       width_plus_1;
    s32       odd_width;
    s16       half_width;
    s16       half_inner;
    u16       odd_width_u16;
    s16       base_x;
    s16       edge_x;
    left                      = (u16)x;
    top                       = (u16)y;
    texture_window            = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor           = (u8*)(texture_window + 1);
    texture_window->pos.y.raw = 240;
    texture_window->pos.x.raw = 0;
    setWH(texture_window, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1, 0xC);
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    clut_x = (((s32)window_style) << 5) + 0x10;
    ;
    setXY0(primitive, left, top);
    primitive->y1 = top;
    primitive->x2 = left;
    primitive->x1 = (s16)(x + 2);
    primitive->x3 = (s16)(x + 2);
    setUV0(primitive, 0, 0);
    primitive->v1 = 0;
    primitive->u2 = 0;
    setRGB0(primitive, 0xAC, 0xAC, 0xAC);
    bottom_v      = (u8)(height + 1);
    bottom_y      = (s16)(y + bottom_v);
    primitive->y2 = bottom_y;
    primitive->y3 = bottom_y;
    primitive->u1 = 2;
    primitive->v2 = bottom_v;
    primitive->u3 = 2;
    primitive->v3 = bottom_v;
    primitive->y0 += 2;
    primitive->y2 -= 3;
    primitive->v0 += 2;
    primitive->v2 -= 3;
    primitive->clut = GetClut(clut_x, 481);
    width_plus_1    = width + 1;

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1, 0x28);
    half_width = (s16)((((u16)width_plus_1) - 4) >> 1);
    half_inner = half_width;
    primitive  = (POLY_FT4*)g_GfxPrimCursor;
    odd_width  = (width - 3) & 1;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, (s16)(x + 2), top, (s16)(((s16)(x + 2)) + half_width), top, (s16)(x + 2), bottom_y,
           (s16)(((s16)(x + 2)) + half_width), bottom_y);
    setUV4(primitive, 0, 0, (u8)half_inner, 0, 0, bottom_v, (u8)half_inner, bottom_v);
    setRGB0(primitive, 0xAC, 0xAC, 0xAC);
    primitive->clut = GetClut(clut_x, 481);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1, 0x28);
    odd_width_u16 = (u16)odd_width;
    primitive     = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y0 = top;
    base_x        = (s16)(x + half_width);
    primitive->x0 = (s16)(base_x + 2);
    primitive->x1 = (s16)(base_x + ((half_width + odd_width) + 2));
    primitive->y1 = top;
    primitive->x2 = (s16)(base_x + 2);
    primitive->y2 = bottom_y;
    primitive->x3 = (s16)(base_x + ((half_width + odd_width) + 2));
    primitive->y3 = bottom_y;
    setUV4(primitive, 0, 0, (u8)(half_inner + odd_width_u16), 0, 0, bottom_v, (u8)(half_inner + odd_width_u16),
           bottom_v);
    setRGB0(primitive, 0xAC, 0xAC, 0xAC);
    primitive->clut = GetClut(clut_x, 481);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1, 0x28);
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y2 = bottom_y;
    primitive->v2 = bottom_v;
    edge_x        = (s16)(x + width_plus_1);
    primitive->x1 = edge_x;
    new_var       = (s16)(edge_x - 2);
    primitive->y1 = top;
    primitive->x3 = edge_x;
    setXY0(primitive, new_var, top);
    primitive->x2 = (s16)(edge_x - 2);
    primitive->y3 = bottom_y;
    setUV0(primitive, 0, 0);
    primitive->u1 = 2;
    primitive->v1 = 0;
    primitive->u2 = 0;
    primitive->u3 = 2;
    primitive->v3 = bottom_v;
    setRGB0(primitive, 0xAC, 0xAC, 0xAC);
    primitive->y1 += 2;
    primitive->y3 -= 3;
    primitive->y2--;
    primitive->v1 += 2;
    primitive->v2--;
    primitive->v3 -= 3;
    primitive->clut = GetClut(clut_x, 481);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1, 0x28);
    texture_window            = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor           = (u8*)(texture_window + 1);
    texture_window->pos.x.raw = 0;
    texture_window->pos.y.raw = 0;
    setWH(texture_window, 256, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1, 0xC);
    func_801AEBA0((s16)(x + 2), (s16)(y + 2), (s16)(width - 4), (s16)(height - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif
