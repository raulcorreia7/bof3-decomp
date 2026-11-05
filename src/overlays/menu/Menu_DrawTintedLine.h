#include <strings.h>

/* Emit a semi-transparent `LineF2` in the requested colour and tpage. One
 * definition shared by the shop, start, Bate and Shisu overlays; each overlay
 * includes this file where the function sits.
 */
/* func_801D36B8 (bate), func_801D4660 (shisu), func_801D9160 (shop), func_801DC658 (start) */
MATCH void Menu_DrawTintedLine(s16 line_x0, s16 line_y0, s16 line_x1, s16 line_y1, u8 color_r, u8 color_g, u8 color_b,
                               u8 tpage) {
    LINE_F2* primitive;
    u8       color0;
    u8       color1;
    u8       color2;
    s16      x0;
    s16      y0;
    s16      x1;
    s16      y1;

    color0 = color_r;
    color1 = color_g;
    color2 = color_b;
    x0     = line_x0;
    y0     = line_y0;
    x1     = line_x1;
    y1     = line_y1;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, tpage, 960, 0), 0);
    GFX_AddPrim(1, 0xC);
    primitive = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(primitive);
    SetSemiTrans(primitive, 1);
    primitive->r0 = color0;
    primitive->g0 = color1;
    primitive->b0 = color2;
    primitive->x0 = x0;
    primitive->y0 = y0;
    primitive->x1 = x1;
    primitive->y1 = y1;
    GFX_AddPrim(1, 0x10);
}
