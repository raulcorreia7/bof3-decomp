#include "engine/slus/slus.h"

#define WINDOW       ((MessageWindowBlock*)D_801490B8)
#define GLYPH        ((POLY_FT4*)g_GfxPrimCursor)

/* The glyph's cell in the font sheet: 31 glyphs of 8 by 12 texels per row, from '0', below the first 72 rows. */
#define GLYPH_INDEX  (*text - '0')
#define GLYPH_U      ((GLYPH_INDEX % 31) * 8)
#define GLYPH_V      (((GLYPH_INDEX / 31) * 12) + 72)

/* Rows the glyph loses for the current row offset. */
#define ROW_OFFSET   g_TextRowOffsets[WINDOW->row_offset_index]
#define GLYPH_BOTTOM (WINDOW->window.text.y + ((u16)((u16)WINDOW->window.cue_counter + 12) - ((s32)(((((s32)((u16)WINDOW->window.cue_counter << 0x10) >> 0xC) + 192) / 12) * ROW_OFFSET) >> 4)))
#define GLYPH_RIGHT  ((u16)WINDOW->window.cue_counter + (WINDOW->window.text.x + 8))

/* Draws one glyph of the message text at the window's text cursor in a palette colour, then advances the cursor. */
MATCH void UI_TextDrawGlyph(s32 color, u8* text) {
    s32 height;
    s32 index;
    s32 width;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 1) & HALF_MASK);
    index       = color & 0xF;
    GLYPH->clut = GetClut(index * 16, STAGE_PALETTE_Y);
    width       = 8;
    if (WINDOW->window.cue_counter < 9) {
        height = 12;
    } else {
        width  = 7;
        height = 11;
    }
    if (*text != STRING_SPACE) {
        GLYPH->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        setUV3(GLYPH, (s8)GLYPH_U, (s8)GLYPH_V, (s8)(width + GLYPH_U), (s8)GLYPH_V, (s8)GLYPH_U, (s8)((s8)GLYPH_V + (height - ROW_OFFSET)));
        GLYPH->u3 = (s8)(width + GLYPH_U);
        GLYPH->v3 = (s8)((s8)GLYPH_V + (height - ROW_OFFSET));
        setRGB0(GLYPH, 0x80, 0x80, 0x80);
        setXY4(GLYPH, (u16)WINDOW->window.text.x, (u16)WINDOW->window.text.y, (s16)GLYPH_RIGHT, (u16)WINDOW->window.text.y, (u16)WINDOW->window.text.x, (s16)GLYPH_BOTTOM, (s16)GLYPH_RIGHT,
               (s16)GLYPH_BOTTOM);
        SetPolyFT4(GLYPH);
        PSX_SET_SEMI_TRANSPARENT(g_GfxPrimCursor);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    }
    g_UIMessageWindow.text.x += (u16)WINDOW->window.cue_counter;
}
