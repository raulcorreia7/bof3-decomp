#include "battle_03.h"

/* func_801EA650 */
MATCH void Battle_UpdateEventPanel(void) {
    BattleEventPanelSteps handlers;
    u8                    index;

    handlers = g_BattleEventPanelSteps;
    handlers.steps[g_UiPanelCurrent->state]();
    func_801D7EB0((s16)g_UiPanelCurrent->pos.x, (s16)g_UiPanelCurrent->pos.y);
    index = BATTLE_PANEL_TASK->selection.slot;
    UI_TextDraw((g_UiPanelCurrent->pos.x + 4), (g_UiPanelCurrent->pos.y + 3), g_BattleEventSlots[index].text_style, TEXT_LENGTH_MAX, g_BattleEventSlots[index].payload);
}
