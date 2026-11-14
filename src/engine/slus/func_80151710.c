#include "engine/slus/slus.h"

/* runs the entry-0 step handler g_MessageWindow.step_id selects (below 0x80 from the active record's table at
 * g_AreaLoads[g_GameAreaId] + 0x34, otherwise the bank copied to g_MessageSteps), clears the record cursor, sets panel
 * state 3 and advances the step byte.
 */
MATCH void func_80151710(void) {
    u32       step;
    u8        count;
    Callback* handlers;

    step = g_MessageWindow.step_id;
    if (step < 128) {
        handlers = ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps;
        handlers[step]();
    } else {
        Message_DispatchTableStep();
    }
    count          = g_UiWindowStep;
    D_801490B8[0]  = 0;
    D_80148357     = 3;
    g_UiWindowStep = count + 1;
}
