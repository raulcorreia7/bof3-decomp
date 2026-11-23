#include "battle_03.h"

/* Draws an enemy's name panel: the two-pass frame around the name and the dimmer lower band. */
#ifdef NON_MATCHING
NON_MATCHING void Battle_DrawEnemyPanel(s32 x, s32 y, s32 slot) {
    s16 color_r;
    s16 color_g;
    s16 color_b;
    s16 draw_x;
    s16 text_x;
    u16 packed_color;
    u8  index;
    s32 panel_x;
    s32 panel_y;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    index        = slot - 3;
    draw_x       = x + 4;
    packed_color = *(u16*)((u8*)D_80033A08 + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    color_r      = (packed_color & 0x1F) * 8;
    color_g      = (packed_color >> 2) & 0xF8;
    color_b      = (packed_color >> 7) & 0xF8;
    Battle_DrawWindowTile(draw_x, (s16)(y + 8), 8, 1);
    Battle_DrawPanelShape(draw_x, (s16)(y + 6), 2, 1);
    Battle_DrawPanelShape(draw_x, (s16)(y + 0x19), 3, 1);
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    draw_x = x;
    Battle_DrawWindowTile(draw_x, (s16)(y + 2), 8, 0);
    text_x = x + 6;
    func_801D9DBC(text_x, (s16)(y + 0xB), 9, 0, 0);
    Battle_DrawPanelShape(draw_x, y, 2, 0);
    Battle_DrawPanelShape(draw_x, (s16)(y + 0x13), 3, 0);
    panel_x = x;
    panel_y = y;
    if (g_BattleEnemyBattlers[index].unk_7F == 1) {
        func_801D9E9C(text_x, (s16)(y + 0xA), g_UiPanelCurrent->unk_0B, g_UiPanelCurrent->flags, 1);
    } else {
        func_801D94D4((s16)(x + 0x24), (s16)(y + 0xC), 0, 0xFFFF);
    }
    UI_TextDrawString((s16)(panel_x + 4), (s16)(panel_y + 3), 0, ENEMY_NAME_LENGTH, g_BattleEnemyBattlers[index].name);
    Battle_DrawPanelLine((s16)(panel_x + 2), (s16)(panel_y + 2), (s16)(panel_x + 0x49), (s16)(panel_y + 2), color_r, color_g, color_b);
    Battle_DrawPanelLine((s16)(panel_x + 2), (s16)(panel_y + 3), (s16)(panel_x + 2), (s16)(panel_y + 0x12), color_r, color_g, color_b);
    color_r -= 0x10;
    color_g -= 0x10;
    color_b -= 0x10;
    color_r = (color_r < 0) ? 0 : ((color_r < 0x100) ? color_r : 0xFF);
    color_g = (color_g < 0) ? 0 : ((color_g < 0x100) ? color_g : 0xFF);
    color_b = (color_b < 0) ? 0 : ((color_b < 0x100) ? color_b : 0xFF);
    Battle_DrawLine((s16)(panel_x + 0x49), (s16)(panel_y + 2), (s16)(panel_x + 0x49), (s16)(panel_y + 0x12), color_r, color_g, color_b);
    Battle_DrawLine((s16)(panel_x + 2), (s16)(panel_y + 0x12), (s16)(panel_x + 0x49), (s16)(panel_y + 0x12), color_r, color_g, color_b);
}
#else
INCLUDE_ASM(Battle_DrawEnemyPanel);
#endif
