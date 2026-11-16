#include "area134_13.h"

MATCH void func_801F40C8(void) {
    Actor* actor;
    u8*    state;

    state = &g_ScriptVars[1];
    if (*state == 0xFE) {
        func_80196070();
    }
    actor          = g_Task;
    g_Game.current = (PartyMember*)&D_80146110;
    TASK_SET(&D_80146110);
    if (g_Game.members[2].pos.x.fixed > 0x33FFFF) {
        *state               = 0xFF;
        g_ScriptVars[2]      = 0;
        g_ScriptVars[3]      = 0;
        g_SceneState.step_05 = 0x14;
        TASK_SET(actor);
        func_80196070();
    } else {
        TASK_SET(actor);
        if (g_Task->timer-- == 0) {
            g_SceneState.timer_06 = 0;
            g_Task->header.mode   = 1;
        }
    }
}
