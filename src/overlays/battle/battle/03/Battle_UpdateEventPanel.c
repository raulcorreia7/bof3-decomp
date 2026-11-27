#include "battle_03.h"

/* func_801EA650 */
MATCH void Battle_UpdateEventPanel(void) {
    BattleEventPanelSteps handlers;
    u8                    index;

    handlers = g_BattleEventPanelSteps;
    handlers.steps[g_UIPanelCurrent->state]();
    func_801D7EB0(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
    index = BATTLE_PANEL_TASK->selection.slot;
    UI_TextDraw((g_UIPanelCurrent->pos.vx + 4), (g_UIPanelCurrent->pos.vy + 3), g_BattleEventSlots[index].text_style, TEXT_LENGTH_MAX, g_BattleEventSlots[index].payload);
}
