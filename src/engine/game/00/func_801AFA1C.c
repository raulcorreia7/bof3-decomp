#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801AFA1C(u8* marks, u8 thumb_top, s16 x, s16 y, s32 thumb_size, s32 total, s32 track_size) {
    u8        total_u8;
    u8        thumb_top_u8;
    u8        thumb_size_u8;
    u8        track_size_u8;
    s32       i;
    TILE*     tile;
    POLY_FT4* poly;
    s32       top;

    total_u8      = total;
    thumb_top_u8  = thumb_top;
    thumb_size_u8 = thumb_size;
    track_size_u8 = track_size;
    i             = 0;
    if (total_u8 != 0) {
        do {
            if (marks[(u16)i] != 0) {
                tile = (TILE*)g_GfxPrimCursor;
                SetTile(tile);
                tile->r0 = 0x80;
                tile->g0 = 0;
                tile->b0 = 0;
                tile->x0 = x + 4;
                tile->y0 = y + (track_size_u8 * (u16)i) / total_u8 + 3;
                tile->w  = 3;
                tile->h  = y + (track_size_u8 * ((u16)i + 1)) / total_u8 + 3 - tile->y0;
                GFX_AddPrim(1, sizeof(TILE));
            }
            i++;
        } while ((u16)i < total_u8);
    }
    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    top         = y + (u8)((track_size_u8 * thumb_top_u8 * 2 + total_u8) / (total_u8 * 2)) + 3;
    poly->x0    = x;
    poly->x2    = x;
    poly->x1    = x + 8;
    poly->x3    = x + 8;
    poly->y0    = top;
    poly->y1    = top;
    poly->y2    = top + thumb_size_u8 * track_size_u8 / total_u8;
    poly->y3    = poly->y2;
    poly->u0    = 0x58;
    poly->v0    = 0x98;
    poly->u1    = 0x60;
    poly->v1    = 0x98;
    poly->u2    = 0x58;
    poly->v2    = 0x9F;
    poly->u3    = 0x60;
    poly->v3    = 0x9F;
    poly->tpage = GetTPage(0, 0, 832, 256);
    poly->clut  = GetClut(176, STAGE_PALETTE_Y + 1);
    poly->r0    = 0x80;
    poly->g0    = 0x80;
    poly->b0    = 0x80;
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801AFA1C);
#endif
