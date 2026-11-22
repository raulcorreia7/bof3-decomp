#include "start_08.h"
#ifdef NON_MATCHING
/* Appends one 12-pixel glyph cell; codes 0x12..0x15 draw wide or two-row cells. */
NON_MATCHING u8* Menu_DrawGlyphAt(s16 x, s16 y, s32 color, u8* glyphs, s32 glyph_left, s32 glyph_right) {
    POLY_FT4* prim;
    u8*       cursor;
    u8        code;
    u8        right;
    s32       left;
    s32       width;
    s32       clut_x;
    u16       clut;
    s32       page_y;
    s32       cell_row;

    Menu_SetGlyphPage(0U);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    cursor = glyphs;
    left   = glyph_left;
    right  = (u8)glyph_right;
    code   = *cursor;
    if ((s32)code < 0x14) {
        if ((s32)code < 0x12) {
            if ((s32)code < 2) {
                width = right - (left & BYTE_MASK);
                if ((s32)code >= 0) {
                    return cursor + 1;
                }
                goto draw_cell;
            }
            width = right - (left & BYTE_MASK);
            goto draw_cell;
        }
        cursor++;
        setXY4(prim, x, y, x + (right - (left & BYTE_MASK)), y, x, y + 0xC, x + (right - (left & BYTE_MASK)), y + 0xC);
        setUV0(prim, (s8)(glyph_left + (((code % 21) & BYTE_MASK) * 0xC)), (s8)((((*cursor) / 21) & BYTE_MASK) * 0xC));
        prim->u1 = (s8)(glyph_right + ((((*cursor) % 21) & BYTE_MASK) * 0xC));
        prim->v1 = (s8)((((*cursor) / 21) & BYTE_MASK) * 0xC);
        prim->u2 = (s8)(glyph_left + ((((*cursor) % 21) & BYTE_MASK) * 0xC));
        prim->v2 = (s8)(((((*cursor) / 21) & BYTE_MASK) * 0xC) + 0xC);
        prim->u3 = (s8)(((((*cursor) % 21) & BYTE_MASK) * 0xC) + glyph_right);
        setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
        prim->v3 = (s8)(((((*cursor) / 21) & BYTE_MASK) * 0xC) + 0xC);
        clut     = GetClut((color & 0xF) * 16, STAGE_PALETTE_Y);
        page_y   = 0x100;
        goto emit;
    }
    if (code != 0x15) {
        width = right - (left & BYTE_MASK);
        if (code == GAME_NONE) {
            return cursor + 1;
        }
    draw_cell:
        setXY4(prim, x, y, x + width, y, x, y + 0xC, x + width, y + 0xC);
        code = *cursor;
        if (code < 0x5B) {
            setUV0(prim, (s8)(left + (((code % 21) & BYTE_MASK) * 0xC)), (s8)((((*cursor) / 21) & BYTE_MASK) * 0xC));
            prim->u1 = (s8)(right + ((((*cursor) % 21) & BYTE_MASK) * 0xC));
            prim->v1 = (s8)((((*cursor) / 21) & BYTE_MASK) * 0xC);
            prim->u2 = (s8)(left + ((((*cursor) % 21) & BYTE_MASK) * 0xC));
            prim->v2 = (s8)(((((*cursor) / 21) & BYTE_MASK) * 0xC) + 0xC);
            prim->u3 = (s8)(right + ((((*cursor) % 21) & BYTE_MASK) * 0xC));
            cell_row = (((*cursor) / 21) & BYTE_MASK) * 3;
        } else {
            prim->v0 = (s8)((((*cursor) + 0x23) / 21) * 0xC);
            prim->u0 = (s8)(left + (((code + 0x23) % 21) * 0xC));
            prim->u1 = (s8)(right + (((code + 0x23) % 21) * 0xC));
            prim->v1 = (s8)(((code + 0x23) / 21) * 0xC);
            prim->u2 = (s8)(left + (((code + 0x23) % 21) * 0xC));
            prim->v2 = (s8)((((code + 0x23) / 21) * 0xC) + 0xC);
            prim->u3 = (s8)(right + (((code + 0x23) % 21) * 0xC));
            cell_row = ((code + 0x23) / 21) * 3;
        }
        prim->v3 = (s8)((cell_row * 4) + 0xC);
        setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
        clut_x = (color & 0xF) * 0x10;
        goto page_low;
    }
    cursor++;
    setXY4(prim, x, y, x + (right - (left & BYTE_MASK)), y, x, y + 0xC, x + (right - (left & BYTE_MASK)), y + 0xC);
    setUV3(prim, (s8)(glyph_left + (((*cursor + 0x64) % 21) * 0xC)), (s8)(((*cursor + 0x64) / 21) * 0xC), (s8)(glyph_right + (((*cursor + 0x64) % 21) * 0xC)), (s8)(((*cursor + 0x64) / 21) * 0xC),
           (s8)(glyph_left + (((*cursor + 0x64) % 21) * 0xC)), (s8)((((*cursor + 0x64) / 21) * 0xC) + 0xC));
    prim->u3 = (s8)((((*cursor + 0x64) % 21) * 0xC) + glyph_right);
    clut_x   = (color & 0xF) * 0x10;
    setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    prim->v3 = (s8)((((*cursor + 0x64) / 21) * 0xC) + 0xC);
page_low:
    clut   = GetClut(clut_x, STAGE_PALETTE_Y);
    page_y = 0;
emit:
    prim->clut  = clut;
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, page_y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    return cursor + 1;
}
#else
INCLUDE_ASM(Menu_DrawGlyphAt);
#endif
