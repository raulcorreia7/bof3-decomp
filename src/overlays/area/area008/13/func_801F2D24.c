#include "area008_13.h"

MATCH void func_801F2D24(void) {
    volatile Actor* previous;

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
    previous                  = g_Task;
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    g_Task                    = (u8*)&g_BattlePartyBattlers[1];
    if (D_80146028 == 4 && D_8014601A == 1) {
        D_801F53F4     = D_801F4674[RANDOM_MASK(7)];
        g_Task         = previous;
        previous->mode = 3;
    }
}
