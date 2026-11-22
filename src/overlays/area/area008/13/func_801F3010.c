#include "area008_13.h"

MATCH void func_801F3010(void) {
    volatile Actor* previous;

    TASK(Actor)->timer = 0;
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        TASK(Actor)->header.mode = 9;
        return;
    }
    previous                  = TASK(Actor);
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    TASK_SET(&g_BattlePartyBattlers[1]);
    D_801460E8 |= 0x40;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 14));
    Script_Select(0x57);
    g_Task                = previous;
    previous->header.mode = 7;
}
