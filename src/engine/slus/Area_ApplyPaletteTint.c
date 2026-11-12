#include "engine/slus/slus.h"

/* shifts the 12 palette planes that the mask pair selects (row mask the 0x200-byte plane, column mask the
 * 16-cell rows): each nonzero 15-bit channel is offset by red, green and blue and clamped to 1..0x1F, into the
 * working copy of the 0x600 offset slice, marking the palette dirty.
 */
MATCH void Area_ApplyPaletteTint(s32 column_mask, s32 row_mask, s32 red, s32 green, s32 blue) {
    s32  plane;
    s32  row;
    s32  cell_index;
    s32  r;
    s32  g;
    s32  b;
    u16* src;
    u16* dst;
    u16* s;
    u16* d;
    u16  cell;

    plane = 3;
    dst   = (u16*)(AREA_PALETTE_WORK + 0x600);
    src   = (u16*)AREA_PALETTE_ARENA_33E00;
    for (; plane < 15; plane++) {
        if (row_mask & 0x1) {
            row = 0;
            s   = src;
            d   = dst;
            for (; row < 16; row++) {
                if (plane != 3 || (column_mask & 0x1)) {
                    for (cell_index = 0; cell_index < 16; cell_index++) {
                        cell = s[row * 16 + cell_index];
                        r    = cell & 0x1F;
                        g    = (cell >> 5) & 0x1F;
                        b    = (cell >> 10) & 0x1F;
                        if (r != 0) {
                            r += red;
                            if (r <= 0) {
                                r = 1;
                            }
                            if (r >= 0x20) {
                                r = 0x1F;
                            }
                        }
                        if (g != 0) {
                            g += green;
                            if (g <= 0) {
                                g = 1;
                            }
                            if (g >= 0x20) {
                                g = 0x1F;
                            }
                        }
                        if (b != 0) {
                            b += blue;
                            if (b <= 0) {
                                b = 1;
                            }
                            if (b >= 0x20) {
                                b = 0x1F;
                            }
                        }
                        d[row * 16 + cell_index] = (s[row * 16 + cell_index] & 0x8000) | (b << 10) | (g << 5) | r;
                    }
                }
                column_mask /= 2;
            }
        }
        row_mask /= 2;
        dst += 0x100;
        src += 0x100;
    }
    g_GfxPalettePending = 1;
}
