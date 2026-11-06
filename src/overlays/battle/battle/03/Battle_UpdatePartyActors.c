#include "battle_03.h"

/* func_801DED54 */
MATCH void Battle_UpdatePartyActors(void) {
    u8 index;

    for (index = 0; index < BATTLE_PARTY_SLOT_COUNT; index++) {
        PartyBattler* battle_work;

        battle_work = &g_BattlePartyBattlers[index];
        g_GameState = battle_work;
        g_Task      = battle_work;

        if ((((battle_work->header.flags & PARTY_BATTLER_FLAG_OCCUPIED) != 0)) &&
            ((battle_work->header.flags & PARTY_BATTLER_FLAG_HANDLER_BUSY) == 0u)) {
            func_8014D290();
        }
    }
}
