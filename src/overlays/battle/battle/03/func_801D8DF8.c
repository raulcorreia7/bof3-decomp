#include "battle_03.h"

/* Draws a party member's battle panel: its frame, name, status glyph, HP gauges and the two rails. */
MATCH void func_801D8DF8(s16 x, s16 y, u8 index) {
    u16 color;
    s16 r;
    s16 g;
    s16 b;
    u8  mode;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    color = BATTLE_WINDOW_COLORS[(LOB(g_WindowStyle) << 5) | 0x10];
    r     = (color & 0x1F) * 8;
    g     = (color >> 2) & 0xF8;
    b     = (color >> 7) & 0xF8;
    Battle_DrawWindowTile((s16)(x + 4), (s16)(y + 8), 8, 1);
    Battle_DrawPanelShape((s16)(x + 4), (s16)(y + 6), 2, 1);
    Battle_DrawPanelShape((s16)(x + 4), (s16)(y + 0x19), 3, 1);
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Battle_DrawWindowTile(x, (s16)(y + 2), 8, 0);
    Battle_DrawPanelShape(x, y, 2, 0);
    Battle_DrawPanelShape(x, (s16)(y + 0x13), 3, 0);
    if (g_Game.members[index].chr.status & 0x4000) {
        mode = 2;
    } else {
        mode = (g_Game.members[index].chr.status & 0xBFC) != 0;
    }
    UI_TextDrawString((s16)(x + 4), (s16)(y + 2), mode, CHARACTER_NAME_LENGTH, g_Game.members[index].chr.name);
    if (g_Game.members[index].chr.status & 0x4000) {
        mode = 2;
    } else {
        mode = (g_Game.members[index].chr.status >> 0xB) & 4;
    }
    func_801DA078((u16)(x + 2), (u16)(y + 0xA), 0);
    func_801D94D4((s16)(x + 0x14), (s16)(y + 0xC), mode, g_Game.members[index].chr.hp);
    mode = (g_Game.members[index].chr.status >> 0xD) & 2;
    TEXT_FormatLiteral(g_UITextFormatBuffer, D_801D0C6C);
    UI_TextDrawGlyphString((s16)(x + 0x28), (s16)(y + 0xA), mode, g_UITextFormatBuffer);
    func_801D94D4((s16)(x + 0x30), (s16)(y + 0xC), mode, g_Game.members[index].chr.stats.max_hp);
    Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 2), (s16)(x + 0x49), (s16)(y + 2), r, g, b);
    Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 3), (s16)(x + 2), (s16)(y + 0x12), r, g, b);
    r -= 0x10;
    g -= 0x10;
    b -= 0x10;
    r = (r < 0) ? 0 : ((r < 0x100) ? r : 0xFF);
    g = (g < 0) ? 0 : ((g < 0x100) ? g : 0xFF);
    b = (b < 0) ? 0 : ((b < 0x100) ? b : 0xFF);
    Battle_DrawLine((s16)(x + 0x49), (s16)(y + 2), (s16)(x + 0x49), (s16)(y + 0x12), r, g, b);
    Battle_DrawLine((s16)(x + 2), (s16)(y + 0x12), (s16)(x + 0x49), (s16)(y + 0x12), r, g, b);
}
