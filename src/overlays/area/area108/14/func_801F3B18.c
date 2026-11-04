#include "area108_14.h"

MATCH void func_801F3B18(void) {
    Actor* saved = g_SpadWork;
    u8     i;

    for (i = 0; i < g_PartySize; i++) {
        g_SpadWork         = (Actor*)&g_BattlePartyBattlers[i];
        g_SpadWork->unk_29 = 6;
    }
    g_SpadWork = saved;
    Actor_Clear();
}
