#include "battle_03.h"

#if BOF3_USE_ASM
INCLUDE_ASM(func_801D8DF8);
#else

MATCH void func_801D8DF8(s32 panel_x, s32 panel_y, u32 index) {
    s16 bar_border_y;
    s16 shadow_component;
    s32 status_text_y;
    s32 battler_index;
    s32 status_mode;
    s32 draw_x;
    s32 hp_text_y;
    s32 panel_bottom_y;
    s32 panel_left_x;
    s32 shadow_blue;
    s32 panel_right_x;
    s32 status_label_y;
    s32 status_value;
    s32 shadow_green;
    u16 packed_color;
    u16 panel_status;
    u16 bar_status;
    u8  blue_component;
    u8  color_r;
    u8  color_g;
    u8  color_b;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    draw_x = panel_x + 4;
    draw_x <<= 0x10;
    draw_x       = draw_x >> 0x10;
    packed_color = *(u16*)(MEM_PTR(u8, 0x80033A08u) + ((g_WindowStyle << 6) | 0x20));
    color_r      = (packed_color & 0x1F) * 8;
    color_g      = (packed_color >> 2) & 0xF8;
    color_b      = (packed_color >> 7) & 0xF8;
    Battle_DrawWindowTile(draw_x, (panel_y + 8), 8U, 1U);
    func_801D9AB4(draw_x, (panel_y + 6), 2, 1);
    func_801D9AB4(draw_x, (panel_y + 0x19), 3, 1);
    GFX_AddDrawMode(GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    draw_x = panel_x << 0x10;
    draw_x = (s16)panel_x;
    Battle_DrawWindowTile(draw_x, (panel_y + 2), 8U, 0U);
    func_801D9AB4(draw_x, panel_y, 2, 0);
    func_801D9AB4(draw_x, (panel_y + 0x13), 3, 0);
    panel_status = g_Game.members[index & BYTE_MASK].chr.status;
    if (panel_status & 0x4000) {
        status_mode = 2;
    } else {
        status_mode = (panel_status & 0xBFC) != 0;
    }
    battler_index = index & BYTE_MASK;
    UI_DrawTextString((panel_x + 4), (panel_y + 2), status_mode, 5U, (const u8*)&g_Game.members[battler_index].chr);
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
    hp_text_y      = hp_text_y >> 0x10;
    blue_component = color_b;
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
    func_801DA5A8(panel_left_x, bar_border_y, (panel_x + 0x49), bar_border_y, color_r, color_g, blue_component);
    func_801DA5A8(panel_left_x, (panel_y + 3), panel_left_x, (panel_y + 0x12), color_r, color_g, blue_component);
    shadow_component = color_r - 0x10;
    if (shadow_component < 0) {
        color_r = 0;
    } else if (shadow_component >= 0x100) {
        color_r = 0xFF;
    } else {
        color_r = shadow_component;
    }
    shadow_component = color_g - 0x10;
    if (shadow_component < 0) {
        color_g = 0;
    } else if (shadow_component >= 0x100) {
        color_g = 0xFF;
    } else {
        color_g = shadow_component;
    }
    shadow_component = blue_component - 0x10;
    if (shadow_component < 0) {
        blue_component = 0;
    } else if (shadow_component >= 0x100) {
        blue_component = 0xFF;
    } else {
        blue_component = shadow_component;
    }
    shadow_blue   = blue_component;
    panel_right_x = panel_x + 0x49;
    panel_right_x <<= 0x10;
    panel_right_x  = panel_right_x >> 0x10;
    panel_bottom_y = panel_y + 0x12;
    panel_bottom_y <<= 0x10;
    panel_bottom_y = panel_bottom_y >> 0x10;
    shadow_green   = color_g;
    shadow_blue &= BYTE_MASK;
    Battle_DrawLine(panel_right_x, (panel_y + 2), panel_right_x, panel_bottom_y, color_r, shadow_green, shadow_blue);
    Battle_DrawLine((panel_x + 2), panel_bottom_y, panel_right_x, panel_bottom_y, color_r, shadow_green, shadow_blue);
}
#endif
