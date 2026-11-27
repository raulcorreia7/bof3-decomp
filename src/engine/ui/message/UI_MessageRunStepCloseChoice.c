#include "engine/slus/slus.h"

/* Runs the step handler of g_UIMessageWindow.step_id (the area table below 0x80, else UI_MessageDispatchStep) and starts the choice panel closing. */
MATCH void UI_MessageRunStepCloseChoice(void) {
    u32       step_id;
    u8        next_step;
    Callback* handlers;

    step_id = g_UIMessageWindow.step_id;
    if (step_id < 128) {
        handlers = ((AreaLoad*)g_AreaLoads[g_GameAreaId])->steps;
        handlers[step_id]();
    } else {
        UI_MessageDispatchStep();
    }
    next_step               = g_UIMessageStep;
    D_801490B8[0]           = 0;
    g_UIPanelTasks[1].state = 3;
    g_UIMessageStep         = next_step + 1;
}
