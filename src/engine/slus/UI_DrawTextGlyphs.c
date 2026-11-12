#include "engine/slus/slus.h"

/* draws a text record through the shared sprite cursor: STRING_COLOR selects the next byte as a
 * palette source, STRING_NOCOLOR restores the saved one, STRING_NEWLINE advances a line, STRING_VAR recurses into a
 * 0x20-byte row, STRING_NUM selects a glyph from the 21-column sheet, and ordinary bytes use the 31-column sheet;
 * glyphs are 8 wide with height from D_8017F580. The second argument budgets the bytes consumed.
 */
MATCH u8* UI_DrawTextGlyphs(u8 flags, u8 len, u8* record) {
    u8* str;
    u8  palette;
    u8  saved;
    u8  count;
    u8  shade;
    s32 height;
    u16 clut;
    u32 index;
    s32 glyph_y;

    str     = record;
    palette = flags;
    count   = len;
    saved   = 0;
    func_8014FC00(0);
    clut   = (flags & 0xF) | STAGE_PALETTE_CLUT;
    index  = (flags & 0xF0) >> 3;
    shade  = g_NumberRowShades[index];
    height = 12 - g_NumberRowShades[index + 1];

    do {
        switch (*str) {
            case STRING_COLOR:
                str++;
                saved   = palette;
                palette = *str;
                clut    = (palette & 0xF) | STAGE_PALETTE_CLUT;
                break;
            case STRING_NOCOLOR:
                palette = saved;
                clut    = (palette & 0xF) | STAGE_PALETTE_CLUT;
                break;
            case STRING_NEWLINE:
                D_80145ACA = D_80145ACE;
                D_80145ACC += 0xC;
                break;
            case STRING_NUM:
                str++;
                ((SPRT*)g_GfxPrimCursor)->u0 = (((*str + 91) % 21) * 12);
                glyph_y                      = ((*str + 0x5B) / 21) * 0xC;
                ((SPRT*)g_GfxPrimCursor)->v0 = (shade + glyph_y);
                setWH(((SPRT*)g_GfxPrimCursor), 8, height);
                func_8014FB80(D_80145ACA, D_80145ACC, clut, shade);
                D_80145ACA += 8;
                break;
            case STRING_VAR:
                str++;
                UI_DrawTextGlyphs(palette & BYTE_MASK, 0x20, &g_TextVariables[*str][0]);
                break;
            case STRING_SPACE:
                D_80145ACA += 8;
                break;
            case STRING_END:
                break;
            default:
                ((SPRT*)g_GfxPrimCursor)->u0 = (((*str - '0') % 31) * 8);
                glyph_y                      = (((*str - '0') / 31) * 0xC) + 0x48;
                ((SPRT*)g_GfxPrimCursor)->v0 = (shade + glyph_y);
                setWH(((SPRT*)g_GfxPrimCursor), 8, height);
                func_8014FB80(D_80145ACA, D_80145ACC, clut, shade);
                D_80145ACA += 8;
                break;
        }
        str++;
    } while (*str != STRING_END && (--count & BYTE_MASK) != 0);
    return str + 1;
}
