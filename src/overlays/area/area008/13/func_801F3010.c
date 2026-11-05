#include "area008_13.h"

MATCH void func_801F3010(void) {
    volatile Actor* previous;

    g_Task->unk_09 = 0;
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->mode = 9;
        return;
    }
    previous                  = g_Task;
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    g_Task                    = (u8*)&g_BattlePartyBattlers[1];
    D_801460E8 |= 0x40;
    SND_PlayCue(EMI_CUE_ID(2, 14));
    Actor_SelectScript(0x57);
    g_Task         = previous;
    previous->mode = 7;
}
