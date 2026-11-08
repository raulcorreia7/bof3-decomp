#include "engine/slus/slus.h"

/* draws a translucent textured quad and its outline at the given
 * screen position, then four corner bars around it.
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 69.08%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_80159B9C(s32 x, s32 y, u16 w, u16 h) {
    s16       x1 = x;
    s16       y1 = y;
    s16       x2;
    s16       y2;
    s16       x3;
    s16       y3;
    TILE*     tile;
    POLY_GT4* poly;
    LINE_F4*  line;
    RECT*     rect;

    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x1, y1);
    w       = w & BYTE_MASK;
    tile->w = w + 1;
    h       = h & BYTE_MASK;
    tile->h = h + 1;
    setRGB0(tile, 0, 0, 0);
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, sizeof(TILE));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->x = 0;
    rect->y = 240;
    setWH(rect, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    poly = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(poly);
    poly->tpage = GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = GetClut(((s8)g_WindowStyle << 5) | 0x10, STAGE_PALETTE_Y + 1);
    x2          = x + w;
    y2          = y + h;
    setRGB0(poly, 255, 255, 255);
    setRGB1(poly, 255, 255, 255);
    setRGB2(poly, 255, 255, 255);
    setRGB3(poly, 255, 255, 255);
    setXY4(poly, x1, y1, x2, y1, x1, y2, x2, y2);
    setUV4(poly, 0, 0, w, 0, 0, h, w, h);
    SetSemiTrans(poly, 1);
    GFX_AddPrim(1, sizeof(POLY_GT4));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->x = 0;
    rect->y = 0;
    setWH(rect, 256, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, 320, 0), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    line = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line);
    x1 = x - 1;
    y1 = y - 1;
    setRGB0(line, 200, 200, 200);
    setXY4(line, x1, y1, x2 + 1, y1, x2 + 1, y2 + 1, x1, y2 + 1);
    GFX_AddPrim(1, sizeof(LINE_F4));

    UI_DrawLine(x1, y1, x1, y2 + 1, 0xC8);
    x3 = x - 2;
    UI_DrawLine(x3, y, x3, y2, 0x8C);
    UI_DrawLine(x2 + 2, y, x2 + 2, y2, 0x8C);
    y3 = y - 2;
    UI_DrawLine(x, y3, x2, y3, 0x8C);
    UI_DrawLine(x, y2 + 2, x2, y2 + 2, 0x8C);
}
#else
INCLUDE_ASM(func_80159B9C);
#endif
