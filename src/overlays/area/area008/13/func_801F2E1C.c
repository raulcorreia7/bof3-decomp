#include "area008_13.h"

MATCH void func_801F2E1C(void) {
    volatile Actor* previous;
    u8              tmp;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->mode = 9;
        return;
    }
    if (g_ScriptVars[1] == 1) {
        g_ScriptVars[2] = 5;
        g_ScriptVars[1] = 2;
        g_Task->mode    = 6;
        return;
    }
    tmp        = (D_801F53F4 - 1);
    D_801F53F4 = tmp;
    if ((tmp & BYTE_MASK) < 2) {
        g_ScriptVars[2]           = 2;
        previous                  = g_Task;
        WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
        TASK_SET(&g_BattlePartyBattlers[1]);
        Actor_SelectScript(1);
        D_801F53F4     = D_801F4680[RANDOM_MASK(3)];
        g_Task         = previous;
        previous->mode = 4;
    }
}
