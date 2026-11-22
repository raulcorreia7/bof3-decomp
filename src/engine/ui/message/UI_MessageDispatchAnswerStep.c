#include "engine/slus/slus.h"

/* dispatches the selection byte g_UiMessageWindow.step_id through the handler table at 0x34 of the current g_AreaLoads bank
 * record (ids below 0x80) or UI_MessageDispatchStep, then sets owner mode 3: a pending area request latches mode 1
 * and advances g_UiMessageStep, a cleared one latches 7; clears D_801490B8. */
MATCH void UI_MessageDispatchAnswerStep(void) {
    u8 id;

    id = g_UiMessageWindow.step_id;
    if (id < 0x80u) {
        ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps[id]();
    } else {
        UI_MessageDispatchStep();
    }

    g_UiPanelTasks[1].state = 3;
    if (g_UiMessageRequest != MESSAGE_NONE) {
        g_UiPanelTasks[0].state = 1;
        g_UiMessageStep         = g_UiMessageStep + 1;
    } else {
        g_UiMessageStep = 7;
    }
    D_801490B8[0] = 0;
}
