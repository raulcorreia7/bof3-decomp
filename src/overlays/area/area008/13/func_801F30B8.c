#include "area008_13.h"

MATCH void func_801F30B8(void) {
    volatile Actor* previous;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->header.mode = 9;
        return;
    }
    previous                  = g_Task;
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    TASK_SET(&g_BattlePartyBattlers[1]);
    if (D_80146028 == 8 && D_8014601A == 1) {
        Actor_SelectScript(1);
        D_801F53F4            = D_801F4680[RANDOM_MASK(3)];
        g_Task                = previous;
        previous->header.mode = 8;
    }
}
