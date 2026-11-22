#include "engine/slus/slus.h"

/* runs the entry-0 step handler g_UiMessageWindow.step_id selects (below 0x80 from the active record's table at
 * g_AreaLoads[g_GameAreaId] + 0x34, otherwise the bank copied to g_UiMessageSteps), clears the record cursor, sets panel
 * state 3 and advances the step byte.
 */
MATCH void func_80151710(void) {
    u32       step;
    u8        count;
    Callback* handlers;

    step = g_UiMessageWindow.step_id;
    if (step < 128) {
        handlers = ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps;
        handlers[step]();
    } else {
        UI_MessageDispatchStep();
    }
    count                   = g_UiMessageStep;
    D_801490B8[0]           = 0;
    g_UiPanelTasks[1].state = 3;
    g_UiMessageStep         = count + 1;
}
