#include "engine/slus/slus.h"
#include "game/character.h"

/* Draws a window panel: a dark translucent tile, the window texture in the current style over it, a
 * grey outline, and a darker line outside each edge. */
/* func_80159B9C */
MATCH void UI_DrawPanelBox(s16 x, s16 y, u8 w, u8 h) {
    s16       right;
    s16       bottom;
    s32       tile_w;
    s32       tile_h;
    u16       width;
    u16       height;
    TILE*     tile;
    POLY_GT4* poly;
    LINE_F4*  line;
    RECT*     rect;

    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    width  = w;
    tile_w = (s16)width + 1;
    setXY0(tile, x, y);
    height  = h;
    tile_h  = (s16)height + 1;
    tile->w = tile_w;
    tile->h = tile_h;
    setRGB0(tile, 0, 0, 0);
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, sizeof(TILE));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->y = 240;
    rect->x = 0;
    rect->w = rect->h = 16;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    poly = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(poly);
    poly->tpage = GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = GetClut(((s8)CHARACTER_BLOCK->window_style << 5) | 0x10, STAGE_PALETTE_Y + 1);
    GFX_SET_RGB_ALL(poly, 255, 255, 255);
    setXY4(poly, x, y, x + tile_w, y, x, y + tile_h, x + tile_w, y + tile_h);
    setUV4(poly, 0, 0, w, 0, 0, h, w, h);
    SetSemiTrans(poly, 1);
    GFX_AddPrim(1, sizeof(POLY_GT4));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->y = 0;
    rect->x = 0;
    rect->w = rect->h = 256;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, 320, 0), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    line = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line);
    setRGB0(line, 200, 200, 200);
    right  = x + width;
    bottom = y + height;
    setXY4(line, x - 1, y - 1, right + 1, y - 1, right + 1, bottom + 1, x - 1, bottom + 1);
    GFX_AddPrim(1, sizeof(LINE_F4));

    UI_DrawLine(x - 1, y - 1, x - 1, bottom + 1, 200);
    UI_DrawLine(x - 2, y, x - 2, bottom, 140);
    UI_DrawLine(right + 2, y, right + 2, bottom, 140);
    UI_DrawLine(x, y - 2, right, y - 2, 140);
    UI_DrawLine(x, bottom + 2, right, bottom + 2, 140);
}
