#include "engine/slus/slus.h"

/* draws a text string's glyph bytes through the shared sprite cursor
 * at (x, y): 0x01 starts a new line 9 lower at the first x, 0xFF skips one
 * glyph, 0x15 maps the next byte into the 32-column sheet and other bytes the
 * 31-column sheet; glyphs are 8 wide. The fourth argument budgets the bytes
 * drawn; returns the byte after the terminator.
 */
MATCH const u8* UI_DrawTextString(s16 x, s16 y, s32 palette, u8 byte_count, const u8* text) {
    u8* str;
    s16 left;
    u16 clut;
    u32 index;
    u8  shade;
    u8  trim;
    s32 glyph_y;
    u8  c;

    left = x;
    str  = (u8*)text;
    func_8014FC00(0);
    clut  = (palette & 0xF) | STAGE_PALETTE_CLUT;
    index = ((u32)palette & 0xF0) >> 3;
    c     = *str;
    /* FAKE: the non-const read keeps the retail load order of the table bytes. */
    shade = ((u8*)g_TextRowShades)[index];
    trim  = ((u8*)g_TextRowShades)[index + 1];

    while (c != 0) {
        if ((byte_count & BYTE_MASK) == 0) {
            break;
        }
        switch (c) {
            case 0x1:
                x = left;
                y += 9;
                break;
            case 0xFF:
                x += 8;
                break;
            case 0x0:
                break;
            case 0x15:
                str++;
                setUV0(((SPRT*)g_GfxPrimCursor), (((*str + 64) % 32) * 8), (shade + ((*str + 64) / 32) * 8));
                setWH(((SPRT*)g_GfxPrimCursor), 8, 8 - trim);
                func_8014FB80(x, y, clut, shade);
                x += 8;
                break;
            default:
                ((SPRT*)g_GfxPrimCursor)->u0 = (((*str - 48) % 31) * 8);
                glyph_y                      = (((*str - 0x30) / 31) * 8) + 0x78;
                ((SPRT*)g_GfxPrimCursor)->v0 = (shade + glyph_y);
                setWH(((SPRT*)g_GfxPrimCursor), 8, 8 - trim);
                func_8014FB80(x, y, clut, shade);
                x += 8;
                break;
        }
        str++;
        c = *str;
        byte_count--;
    }
    return str + 1;
}
