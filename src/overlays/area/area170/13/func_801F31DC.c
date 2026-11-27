#include "area170_13.h"

/* Draws the three glyph panels, the arrow between them and, every other frame, the row bars of
 * the panel SELF(Actor)->unk_06 selects. */
MATCH void func_801F31DC(s32 x, s32 y) {
    s32 panel_x;
    s32 offset;
    s16 left;
    s16 right;
    s16 top;
    s16 middle;
    s16 bottom;

    func_801F3838(0);
    func_801F3594(x, (s16)(y + 5), (s16)(x + 5), y, x, (s16)(y + 0x55), (s16)(x + 5), (s16)(y + 0x5A), 0, 0x80, 0, 1);
    func_801F3594((s16)(x + 5), y, (s16)(x + 0x131), y, (s16)(x + 5), (s16)(y + 0x5A), (s16)(x + 0x131), (s16)(y + 0x5A), 0, 0x80, 0, 1);
    func_801F3594((s16)(x + 0x131), y, (s16)(x + 0x136), (s16)(y + 5), (s16)(x + 0x131), (s16)(y + 0x5A), (s16)(x + 0x136), (s16)(y + 0x55), 0, 0x80, 0, 1);
    func_801F2FA0((s16)(x + 9), (s16)(y + 0xA), D_801F58D0[0][0], D_801F5990[0]);
    func_801F2FA0((s16)(x + 0x6D), (s16)(y + 0xA), D_801F58D0[1][0], D_801F5990[1]);
    func_801F2FA0((s16)(x + 0xD1), (s16)(y + 0xA), D_801F58D0[2][0], D_801F5990[2]);

    panel_x = x - 1;
    if (((g_FrameCount >> 4) & 1) == 0) {
        return;
    }
    top    = (s16)(y + 0x29);
    middle = (s16)(y + 0x2D);
    bottom = (s16)(y + 0x31);
    func_801F3698((s16)(panel_x + SELF(Actor)->unk_06 * 100 + 7), top, (s16)(panel_x + SELF(Actor)->unk_06 * 100 + 3), middle, (s16)(panel_x + SELF(Actor)->unk_06 * 100 + 7), bottom, 0xC8, 0xC8, 0xC8, 0);
    func_801F3698((s16)(panel_x + (s16)(SELF(Actor)->unk_06 * 100 + 100) + 4), top, (s16)(panel_x + (s16)(SELF(Actor)->unk_06 * 100 + 100) + 8), middle, (s16)(panel_x + (s16)(SELF(Actor)->unk_06 * 100 + 100) + 4), bottom, 0xC8, 0xC8, 0xC8, 0);
    offset = SELF(Actor)->unk_06 * 100 + 0xA;
    left   = (s16)(panel_x + offset);
    right  = (s16)(panel_x + offset + 0x5A);
    top    = (s16)(y + 0xA);
    bottom = (s16)(y + 0x50);
    func_801F3774(left, top, right, top, 0xC8, 0xC8, 0xC8, 0);
    func_801F3774(left, top, left, bottom, 0xC8, 0xC8, 0xC8, 0);
    func_801F3774(left, bottom, right, bottom, 0xC8, 0xC8, 0xC8, 0);
    func_801F3774(right, top, right, bottom, 0xC8, 0xC8, 0xC8, 0);
}
