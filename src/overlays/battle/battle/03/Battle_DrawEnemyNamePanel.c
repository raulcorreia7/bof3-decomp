#include "battle_03.h"

MATCH void Battle_DrawEnemyNamePanel(s32 x, s32 y, s32 slot) {
    u8  index;
    u16 color;
    u8  r;
    u8  g;
    u8  b;
    /* FAKE: retail keeps panel_x in s2 and reuses one temp for the second value; no clean-C shape allocates it so. */
    FAKE_REG(s32, panel_x, "s2");
    s32 panel_y;
    s32 new_var;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    new_var = (s16)(y + 2);
    index   = slot - 3;
    /* FAKE: retail reads g_WindowStyle as s8. */
    color   = *(u16*)(MEM_PTR(u8, 0x80033A08u) + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r       = PSX_COLOR_R(color) << 3;
    g       = PSX_COLOR_G(color) << 3;
    b       = PSX_COLOR_B(color) << 3;
    Battle_DrawWindowTile(x, new_var, 8, 1);
    func_801D9DBC((x + 6), ((new_var = y) + 0xB), 9, 0, 0);
    func_801D9AB4(x, y, 2, 1);
    func_801D9AB4(x, (y + 0x13), 3, 1);
    panel_x = x;
    panel_y = y;
    if (g_BattleEnemyBattlers[index].unk_7F == 1) {
        func_801D9E9C((x + 6), (y + 0xA), FIELD(u8, (u8*)g_MenuCurrentPanel, 0xBu), FIELD(u8, (u8*)g_MenuCurrentPanel, 0xDu), 1);
    } else {
        func_801D94D4((s16)(x + 0x24), (s16)(y + 0xC), 0, 0xFFFF);
    }
    if (func_801DA69C(index) != 0) {
        UI_DrawTextString((panel_x + 4), (panel_y + 3), 0, 8, (const u8*)g_BattleEnemyBattlers[index].name);
    }
    func_801DA5A8((panel_x + 2), (panel_y + 2), (panel_x + 0x49), (panel_y + 2), r, g, b);
    func_801DA5A8((panel_x + 2), (panel_y + 3), (panel_x + 2), (panel_y + 0x12), r, g, b);
    new_var = (panel_y + 2);
    func_801DA4B4((panel_x + 0x49), new_var, (panel_x + 0x49), (panel_y + 0x12), r, g, b);
    func_801DA4B4((panel_x + 2), (panel_y + 0x12), (panel_x + 0x49), (panel_y + 0x12), r, g, b);
}
