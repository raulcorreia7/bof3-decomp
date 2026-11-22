#include "area134_13.h"

MATCH void func_801F3440(void) {
    Actor* actor;
    u8     step;

    actor      = TASK(Actor);
    D_80146250 = &D_80146110;
    TASK_SET(&D_80146110);
    if (D_80146144 > 0x33FFFF) {
        g_ScriptVars[1] = 0xFF;
        step            = 0x14;
    } else {
        g_ScriptVars[1] = 0xFE;
        step            = 0x1E;
    }
    g_ScriptVars[2]         = 0;
    g_ScriptVars[3]         = 0;
    g_ScenarioState.step_05 = step;
    TASK_SET(actor);
    func_80196070();
}
