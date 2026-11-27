#include "battle_03.h"

MATCH void func_801E9538(void) {
    u8 index;
    u8 count;

    index = BATTLE_PANEL_TASK->selection.slot;
    count = Battle_CountMessageChars(g_BattleEventSlots[index].payload);
    func_801D8270(g_UIPanelCurrent->pos.vx - 0x10, g_UIPanelCurrent->pos.vy);
    index = BATTLE_PANEL_TASK->selection.slot;
    UI_TextDraw((g_UIPanelCurrent->pos.vx - count * 4 + 38), (g_UIPanelCurrent->pos.vy + 3), g_BattleEventSlots[index].text_style, 18u, g_BattleEventSlots[index].payload);
}
