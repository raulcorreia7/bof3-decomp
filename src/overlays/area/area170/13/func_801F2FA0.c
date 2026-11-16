#include "area170_13.h"

/* Draws the glyph panel at (x, y): a 90 by 70 box, ten column and eight row lines, then the
 * 9 by 7 glyph grid that starts at the phase column of the glyph sheet. */
MATCH void func_801F2FA0(s16 x, s16 y, s8* glyphs, u8 phase) {
    s16 px;
    s16 py;
    u8  column;
    u8  row;
    u8  glyph_column;
    u8  glyph_row;

    func_801F3838(2);
    func_801F3594(x, y, x + 90, y, x, y + 70, x + 90, y + 70, 0x40, 0x40, 0x40, 1);
    func_801F3838(1);
    for (column = 0; column < 10; column++) {
        px = x + column * 10;
        func_801F3774(px, y, px, y + 69, 0x96, 0x96, 0x96, 0);
    }
    for (row = 0; row < 8; row++) {
        py = y + row * 10;
        func_801F3774(x, py, x + 89, py, 0x96, 0x96, 0x96, 0);
    }
    for (glyph_column = 0; glyph_column < 9; glyph_column++) {
        px = x + glyph_column * 10;
        for (glyph_row = 0; glyph_row < 7; glyph_row++) {
            func_801F388C(px, (s16)(y + glyph_row * 10), glyphs[glyph_row * 9 + phase]);
        }
        phase++;
        if (phase >= 9) {
            phase = 0;
        }
    }
}
