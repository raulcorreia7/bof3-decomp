#include "battle_03.h"

extern u32 D_801EB4F4[][3];
extern u8  D_801EB4FA[][12];

MATCH void func_801EA650(void) {
    BattleHandlerTable3 handlers;
    u8                  index;

    handlers = D_801D0FF8;
    handlers.handlers[g_MenuCurrentPanel->state]();
    func_801D7EB0((s16)g_MenuCurrentPanel->x, (s16)g_MenuCurrentPanel->y);
    index = BATTLE_PANEL_TASK->cell_0A.slot;
    UI_DrawText((s16)(g_MenuCurrentPanel->x + 4), (s16)(g_MenuCurrentPanel->y + 3), D_801EB4FA[index][0], 0xFFu,
                (u8*)D_801EB4F4[index][0]);
}
