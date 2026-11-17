#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D8DF8(s32 panel_x, s32 panel_y, u32 index) {
    s16 color_r;
    s16 color_g;
    s16 color_b;
    s32 status_mode;
    s32 draw_x;
    s32 battler_index;
    s32 panel_left_x;
    s32 panel_right_x;
    s32 panel_bottom_y;
    s32 bar_border_y;
    s32 hp_text_y;
    s32 status_label_y;
    s32 status_text_y;
    s32 status_value;
    u16 packed_color;
    u16 panel_status;
    u16 bar_status;
    u8  color_byte;
    s8* style;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    draw_x = panel_x + 4;
    draw_x <<= 0x10;
    draw_x       = draw_x >> 0x10;
    style        = &g_WindowStyle;
    packed_color = *(u16*)(MEM_PTR(u8, 0x80033A08u) + ((((s32)*style) << 6) | 0x20));
    color_r      = (packed_color & 0x1F) * 8;
    color_g      = (packed_color >> 2) & 0xF8;
    color_b      = (packed_color >> 7) & 0xF8;
    Battle_DrawWindowTile(draw_x, (panel_y + 8), 8U, 1U);
    Battle_DrawPanelShape(draw_x, (panel_y + 6), 2, 1);
    Battle_DrawPanelShape(draw_x, (panel_y + 0x19), 3, 1);
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    draw_x = panel_x << 0x10;
    draw_x = (s16)panel_x;
    Battle_DrawWindowTile(draw_x, (panel_y + 2), 8U, 0U);
    Battle_DrawPanelShape(draw_x, panel_y, 2, 0);
    Battle_DrawPanelShape(draw_x, (panel_y + 0x13), 3, 0);
    panel_status = g_Game.members[index & BYTE_MASK].chr.status;
    if (panel_status & 0x4000) {
        status_mode = 2;
    } else {
        status_mode = (panel_status & 0xBFC) != 0;
    }
    battler_index = index & BYTE_MASK;
    UI_DrawTextString((panel_x + 4), (panel_y + 2), status_mode, CHARACTER_NAME_LENGTH, (const u8*)&g_Game.members[battler_index].chr);
    bar_status = g_Game.members[battler_index].chr.status;
    if (bar_status & 0x4000) {
        status_mode = 2;
    } else {
        status_mode = (bar_status >> 0xB) & 0x4;
    }
    panel_left_x   = panel_x + 2;
    status_label_y = panel_y + 0xA;
    func_801DA078(panel_left_x & HALF_MASK, status_label_y & HALF_MASK, 0);
    hp_text_y = panel_y + 0xC;
    hp_text_y <<= 0x10;
    hp_text_y  = hp_text_y >> 0x10;
    color_byte = color_b;
    func_801D94D4((s16)(panel_x + 0x14), hp_text_y, status_mode, (u8)g_Game.members[battler_index].chr.hp);
    status_mode = ((u8)g_Game.members[battler_index].chr.status >> 0xD) & 0x2;
    TEXT_FormatLiteral(g_UiFormatBuffer, D_801D0C6C);
    status_label_y <<= 0x10;
    status_text_y = status_label_y >> 0x10;
    status_value  = status_mode & BYTE_MASK;
    UI_DrawGlyphString((panel_x + 40), status_text_y, status_value, (u8*)g_UiFormatBuffer);
    func_801D94D4((s16)(panel_x + 0x30), hp_text_y, status_value, (u8)g_Game.members[battler_index].chr.stats.max_hp);
    panel_left_x <<= 0x10;
    panel_left_x = panel_left_x >> 0x10;
    bar_border_y = panel_y + 2;
    Battle_DrawPanelLine(panel_left_x, bar_border_y, (panel_x + 0x49), bar_border_y, color_r, color_g, color_b);
    Battle_DrawPanelLine(panel_left_x, (panel_y + 3), panel_left_x, (panel_y + 0x12), color_r, color_g, color_b);
    color_r -= 0x10;
    if (color_r < 0) {
        color_r = 0;
    } else if (color_r >= 0x100) {
        color_r = 0xFF;
    }
    color_g -= 0x10;
    if (color_g < 0) {
        color_g = 0;
    } else if (color_g >= 0x100) {
        color_g = 0xFF;
    }
    color_b -= 0x10;
    if (color_b < 0) {
        color_b = 0;
    } else if (color_b >= 0x100) {
        color_b = 0xFF;
    }
    panel_right_x = panel_x + 0x49;
    panel_right_x <<= 0x10;
    panel_right_x  = panel_right_x >> 0x10;
    panel_bottom_y = panel_y + 0x12;
    panel_bottom_y <<= 0x10;
    panel_bottom_y = panel_bottom_y >> 0x10;
    Battle_DrawLine(panel_right_x, (panel_y + 2), panel_right_x, panel_bottom_y, color_r, color_g, color_b);
    Battle_DrawLine((panel_x + 2), panel_bottom_y, panel_right_x, panel_bottom_y, color_r, color_g, color_b);
}
#else
INCLUDE_ASM(func_801D8DF8);
#endif
