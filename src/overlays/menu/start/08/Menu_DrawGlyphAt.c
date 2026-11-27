#include "start_08.h"

#ifdef NON_MATCHING
#define GLYPH_COL(c) ((u8)((c) % 21))
#define GLYPH_ROW(c) ((u8)((c) / 21))

NON_MATCHING u8* Menu_DrawGlyphAt(s16 x, s16 y, u8 color, u8* cursor, u8 glyph_left, u8 glyph_right) {
    POLY_FT4* poly;
    int       code;
    u8        left8;
    u8        right8;
    s16       x1;
    s16       y1;

    left8  = glyph_left;
    right8 = glyph_right;
    Menu_SetGlyphPage(0);
    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    code = *cursor;
    switch (code) {
        case 0:
        case 1:
        case 255:
            return cursor + 1;
        case 21:
            cursor += 1;
            x1 = x + (right8 - left8);
            y1 = y + 12;
            setXY4(poly, x, y, x1, y, x, y1, x1, y1);
            poly->u0 = glyph_left + ((*cursor + 0x64) % 21) * 12;
            poly->v0 = ((*cursor + 0x64) / 21) * 12;
            poly->u1 = glyph_right + ((*cursor + 0x64) % 21) * 12;
            poly->v1 = ((*cursor + 0x64) / 21) * 12;
            poly->u2 = glyph_left + ((*cursor + 0x64) % 21) * 12;
            poly->v2 = ((*cursor + 0x64) / 21) * 12 + 12;
            poly->u3 = ((*cursor + 0x64) % 21) * 12 + glyph_right;
            poly->v3 = ((*cursor + 0x64) / 21) * 12 + 12;
            setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            poly->clut  = GetClut((color & 0xF) * 16, STAGE_PALETTE_Y);
            poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
            break;
        case 18:
        case 19:
            cursor += 1;
            x1 = x + (right8 - left8);
            y1 = y + 12;
            setXY4(poly, x, y, x1, y, x, y1, x1, y1);
            poly->u0 = glyph_left + GLYPH_COL(*cursor) * 12;
            poly->v0 = GLYPH_ROW(*cursor) * 12;
            poly->u1 = glyph_right + GLYPH_COL(*cursor) * 12;
            poly->v1 = GLYPH_ROW(*cursor) * 12;
            poly->u2 = glyph_left + GLYPH_COL(*cursor) * 12;
            poly->v2 = GLYPH_ROW(*cursor) * 12 + 12;
            poly->u3 = GLYPH_COL(*cursor) * 12 + glyph_right;
            poly->v3 = GLYPH_ROW(*cursor) * 12 + 12;
            setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            poly->clut  = GetClut((color & 0xF) * 16, STAGE_PALETTE_Y);
            poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 256);
            break;
        default:
            x1 = x + (right8 - left8);
            y1 = y + 12;
            setXY4(poly, x, y, x1, y, x, y1, x1, y1);
            if (*cursor < 0x5B) {
                poly->u0 = left8 + GLYPH_COL(*cursor) * 12;
                poly->v0 = GLYPH_ROW(*cursor) * 12;
                poly->u1 = right8 + GLYPH_COL(*cursor) * 12;
                poly->v1 = GLYPH_ROW(*cursor) * 12;
                poly->u2 = left8 + GLYPH_COL(*cursor) * 12;
                poly->v2 = GLYPH_ROW(*cursor) * 12 + 12;
                poly->u3 = right8 + GLYPH_COL(*cursor) * 12;
                poly->v3 = GLYPH_ROW(*cursor) * 12 + 12;
            } else {
                poly->u0 = left8 + ((*cursor + 0x23) % 21) * 12;
                poly->v0 = ((*cursor + 0x23) / 21) * 12;
                poly->u1 = right8 + ((*cursor + 0x23) % 21) * 12;
                poly->v1 = ((*cursor + 0x23) / 21) * 12;
                poly->u2 = left8 + ((*cursor + 0x23) % 21) * 12;
                poly->v2 = ((*cursor + 0x23) / 21) * 12 + 12;
                poly->u3 = right8 + ((*cursor + 0x23) % 21) * 12;
                poly->v3 = ((*cursor + 0x23) / 21) * 12 + 12;
            }
            setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            poly->clut  = GetClut((color & 0xF) * 16, STAGE_PALETTE_Y);
            poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 0);
            break;
    }
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    return cursor + 1;
}
#else
INCLUDE_ASM(Menu_DrawGlyphAt);
#endif
