#include "engine/game/00/game_00.h"

/* func_801AFA1C */
/* Draws a list scrollbar with its row marks and thumb. */
#ifdef NON_MATCHING
NON_MATCHING void UI_ListDrawScrollbar(u8* marks, u8 thumb_top, s16 x, s16 y, u8 thumb_size, u8 total, u8 track_size) {
    s32       i;
    TILE*     tile;
    POLY_FT4* poly;
    u16       top;
    u16       n;

    i = 0;
    n = total;
    if (n != 0) {
        do {
            if (marks[(u16)i] != 0) {
                tile = (TILE*)g_GfxPrimCursor;
                SetTile(tile);
                setRGB0(tile, 0x80, 0, 0);
                setXY0(tile, x + 4, y + (track_size * (u16)i) / total + 3);
                tile->w = 3;
                tile->h = y + (track_size * ((u16)i + 1)) / total + 3 - tile->y0;
                GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
            }
            i++;
        } while ((u16)i < total);
    }
    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    top         = y + (u8)((track_size * thumb_top * 2 + total) / (total * 2)) + 3;
    poly->x0    = x;
    poly->x2    = x;
    poly->x1    = x + 8;
    poly->x3    = x + 8;
    poly->y0    = top;
    poly->y1    = top;
    poly->y2    = top + thumb_size * track_size / total;
    poly->y3    = poly->y2;
    poly->u0    = 0x58;
    poly->v0    = 0x98;
    poly->u1    = 0x60;
    poly->v1    = 0x98;
    poly->u2    = 0x58;
    poly->v2    = 0x9F;
    poly->u3    = 0x60;
    poly->v3    = 0x9F;
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256);
    poly->clut  = GetClut(176, STAGE_PALETTE_Y + 1);
    poly->r0    = 0x80;
    poly->g0    = 0x80;
    poly->b0    = 0x80;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(UI_ListDrawScrollbar);
#endif
