#include "battle_03.h"

MATCH void func_801E9538(void) {
    u8 index;
    u8 count;

    index = BATTLE_PANEL_TASK->selection.slot;
    count = Battle_CountMessageChars((u8*)D_801EB4F4[index][0]);
    func_801D8270((s16)g_UiPanelCurrent->pos.x - 0x10, (s16)g_UiPanelCurrent->pos.y);
    index = BATTLE_PANEL_TASK->selection.slot;
    UI_TextDraw((g_UiPanelCurrent->pos.x - count * 4 + 38), (g_UiPanelCurrent->pos.y + 3), D_801EB4FA[index][0], 18u, (u8*)D_801EB4F4[index][0]);
}
