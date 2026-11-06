#include "area008_13.h"

MATCH void func_801F2C88(void) {
    volatile Actor* previous;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->header.mode = 9;
        return;
    }

    previous                  = g_Task;
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    TASK_SET(&g_BattlePartyBattlers[1]);
    D_801460E8 |= 0x40;
    Actor_SelectScript(0x10);
    g_ScriptVars[2]       = 1;
    g_Task                = previous;
    previous->header.mode = 2;
}
