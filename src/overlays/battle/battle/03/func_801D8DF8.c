#include "battle_03.h"

/* Draws a party member's battle panel: its frame, name, status glyph, HP gauges and the two rails. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8DF8(s32 panel_x, s32 panel_y, u32 index) {
    u16 color;
    u16 status;
    s16 r;
    s16 g;
    s16 b;
    s32 mode;
    s32 left_x;
    s32 label_y;
    s16 value_y;
    u8  glyph_mode;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    color = *(u16*)(((u8*)&D_80033A08) + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;
    Battle_DrawWindowTile(panel_x + 4, panel_y + 8, 8, 1);
    Battle_DrawPanelShape(panel_x + 4, panel_y + 6, 2, 1);
    Battle_DrawPanelShape(panel_x + 4, panel_y + 0x19, 3, 1);
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Battle_DrawWindowTile(panel_x, panel_y + 2, 8, 0);
    Battle_DrawPanelShape(panel_x, panel_y, 2, 0);
    Battle_DrawPanelShape(panel_x, panel_y + 0x13, 3, 0);
    status = g_Game.members[index & BYTE_MASK].chr.status;
    if (status & 0x4000) {
        mode = 2;
    } else {
        mode = (status & 0xBFC) != 0;
    }
    UI_TextDrawString((panel_x + 4), (panel_y + 2), mode, CHARACTER_NAME_LENGTH, g_Game.members[index & BYTE_MASK].chr.name);
    status = g_Game.members[index & BYTE_MASK].chr.status;
    if (status & 0x4000) {
        mode = 2;
    } else {
        mode = (status >> 0xB) & 4;
    }
    left_x  = panel_x + 2;
    label_y = panel_y + 0xA;
    func_801DA078((u16)left_x, (u16)label_y, 0);
    value_y = panel_y + 0xC;
    func_801D94D4((s16)(panel_x + 0x14), value_y, mode, g_Game.members[index & BYTE_MASK].chr.hp);
    TEXT_FormatLiteral(g_UiTextFormatBuffer, D_801D0C6C);
    mode       = (g_Game.members[index & BYTE_MASK].chr.status >> 0xD) & 2;
    glyph_mode = mode;
    UI_TextDrawGlyphString((panel_x + 0x28), label_y, glyph_mode, g_UiTextFormatBuffer);
    func_801D94D4((s16)(panel_x + 0x30), value_y, glyph_mode, g_Game.members[index & BYTE_MASK].chr.stats.max_hp);
    Battle_DrawPanelLine(left_x, panel_y + 2, panel_x + 0x49, panel_y + 2, r, g, b);
    Battle_DrawPanelLine(left_x, panel_y + 3, left_x, panel_y + 0x12, r, g, b);
    r -= 0x10;
    if (r < 0) {
        r = 0;
    } else if (r >= 0x100) {
        r = 0xFF;
    }
    g -= 0x10;
    if (g < 0) {
        g = 0;
    } else if (g >= 0x100) {
        g = 0xFF;
    }
    b -= 0x10;
    if (b < 0) {
        b = 0;
    } else if (b >= 0x100) {
        b = 0xFF;
    }
    Battle_DrawLine(panel_x + 0x49, panel_y + 2, panel_x + 0x49, panel_y + 0x12, r, g, b);
    Battle_DrawLine(panel_x + 2, panel_y + 0x12, panel_x + 0x49, panel_y + 0x12, r, g, b);
}
#else
INCLUDE_ASM(func_801D8DF8);
#endif
