#include "battle_15.h"

/* Battler status words, one u16 per 0x140-byte player row. */
/* Battler status words, one u16 per 0x118-byte enemy row. */

MATCH void func_8009E07C(void) {
    volatile u8* state;
    s32          battler;
    u16          status;

    battler = LOBU(g_BattleTarget);
    if (battler < 3u) {
        status = g_Game.members[battler].chr.status & STATUS_KO;
    } else {
        battler -= 3;
        status = g_BattleEnemyBattlers[battler].status & STATUS_KO;
    }
    if (status != 0) {
        state                           = &g_BattleTarget;
        g_BattleTargetRecord->hp_change = -1;
        func_800A36F0(*state, 0x4000U);
        if (*state < 3u) {
            g_BattleLivingPartyCount += 1;
        } else {
            g_BattleLivingEnemyCount += 1;
        }
    } else {
        g_BattleTargetRecord->hp_change = 0;
    }
}
