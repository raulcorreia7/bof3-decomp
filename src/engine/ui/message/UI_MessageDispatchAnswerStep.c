#include "engine/slus/slus.h"

/* dispatches the selection byte g_UIMessageWindow.step_id through the handler table at 0x34 of the current g_AreaLoads bank
 * record (ids below 0x80) or UI_MessageDispatchStep, then sets owner mode 3: a pending area request latches mode 1
 * and advances g_UIMessageStep, a cleared one latches 7; clears D_801490B8. */
MATCH void UI_MessageDispatchAnswerStep(void) {
    u8 id;

    id = g_UIMessageWindow.step_id;
    if (id < 0x80u) {
        ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps[id]();
    } else {
        UI_MessageDispatchStep();
    }

    g_UIPanelTasks[1].state = 3;
    if (g_UIMessageRequest != MESSAGE_NONE) {
        g_UIPanelTasks[0].state = 1;
        g_UIMessageStep         = g_UIMessageStep + 1;
    } else {
        g_UIMessageStep = 7;
    }
    D_801490B8[0] = 0;
}
