#include "area135_14.h"

MATCH void func_801F44E0(void) {
    u8 slot = (PartyBattler*)g_GameState - g_BattlePartyBattlers;

    if (slot != 0) {
        g_SpadWork->direction_08 = D_80145E98;
        Actor_SelectScript(g_SpadWork->direction_08);
    }
}
