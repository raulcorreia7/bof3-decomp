#include "battle_03.h"

MATCH void func_801EA650(void) {
    BattlePanel6States handlers;
    u8                 index;

    handlers = D_801D0FF8;
    handlers.states[g_MenuCurrentPanel->state]();
    func_801D7EB0((s16)g_MenuCurrentPanel->pos.x, (s16)g_MenuCurrentPanel->pos.y);
    index = BATTLE_PANEL_TASK->cell_0A.slot;
    UI_DrawText((g_MenuCurrentPanel->pos.x + 4), (g_MenuCurrentPanel->pos.y + 3), D_801EB4FA[index][0], 255u, (u8*)D_801EB4F4[index][0]);
}
