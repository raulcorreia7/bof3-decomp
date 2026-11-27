#include "battle_03.h"

/* func_801EA650 */
MATCH void Battle_UpdateEventPanel(void) {
    BattleEventPanelSteps handlers;
    u8                    index;

    handlers = g_BattleEventPanelSteps;
    handlers.steps[g_UiPanelCurrent->state]();
    func_801D7EB0(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy);
    index = BATTLE_PANEL_TASK->selection.slot;
    UI_TextDraw((g_UiPanelCurrent->pos.vx + 4), (g_UiPanelCurrent->pos.vy + 3), g_BattleEventSlots[index].text_style, TEXT_LENGTH_MAX, g_BattleEventSlots[index].payload);
}
