#include "engine/slus/slus.h"

/* draws a translucent textured quad and its outline at the given
 * screen position, then four corner bars around it.
 */
/* Deferred coordinate initialization leaves the saved-register difference at +0x04; pinned arguments change the frame size. */
#ifdef NON_MATCHING
NON_MATCHING void func_80159B9C(s32 x, s32 y, s32 w, s32 h) {
    s16       left;
    s16       top;
    s32       edge_x;
    s32       edge_y;
    s32       right;
    s32       bottom;
    s32       tile_w;
    s32       tile_h;
    u16       width;
    u16       height;
    TILE*     tile;
    POLY_GT4* poly;
    LINE_F4*  line;
    RECT*     rect;

    left = x;
    top  = y;
    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    width  = w & BYTE_MASK;
    tile_w = width + 1;
    setXY0(tile, left, top);
    height  = h & BYTE_MASK;
    tile_h  = height + 1;
    tile->w = tile_w;
    tile->h = tile_h;
    setRGB0(tile, 0, 0, 0);
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, sizeof(TILE));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->y = 240;
    rect->x = 0;
    setWH(rect, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    poly = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(poly);
    poly->tpage = GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = GetClut(((s8)g_WindowStyle << 5) | 0x10, STAGE_PALETTE_Y + 1);
    setRGB0(poly, 255, 255, 255);
    setRGB1(poly, 255, 255, 255);
    setRGB2(poly, 255, 255, 255);
    setRGB3(poly, 255, 255, 255);
    setXY4(poly, left, top, x + tile_w, top, left, y + tile_h, x + tile_w, y + tile_h);
    setUV4(poly, 0, 0, w, 0, 0, h, w, h);
    SetSemiTrans(poly, 1);
    GFX_AddPrim(1, sizeof(POLY_GT4));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += 8;
    rect->y = 0;
    rect->x = 0;
    setWH(rect, 256, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, 320, 0), rect);
    GFX_AddPrim(1, sizeof(DR_MODE));

    line = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line);
    edge_x = x - 1;
    edge_y = y - 1;
    setRGB0(line, 200, 200, 200);
    right  = x + width;
    bottom = y + height;
    setXY4(line, edge_x, edge_y, right + 1, edge_y, right + 1, bottom + 1, edge_x, bottom + 1);
    GFX_AddPrim(1, sizeof(LINE_F4));

    UI_DrawLine((s16)edge_x, (s16)edge_y, (s16)edge_x, (s16)(bottom + 1), 200);
    UI_DrawLine((s16)(x - 2), (s16)y, (s16)(x - 2), (s16)bottom, 140);
    UI_DrawLine((s16)(right + 2), (s16)y, (s16)(right + 2), (s16)bottom, 140);
    UI_DrawLine((s16)x, (s16)(y - 2), (s16)right, (s16)(y - 2), 140);
    UI_DrawLine((s16)x, (s16)(bottom + 2), (s16)right, (s16)(bottom + 2), 140);
}
#else
INCLUDE_ASM(func_80159B9C);
#endif
