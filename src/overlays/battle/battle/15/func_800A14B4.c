#include "battle_15.h"

typedef struct BattleEnemyFlag118 {
    u32 flags;
    u8  pad_04[0x114];
} BattleEnemyFlag118;

/* sets the selection-suppress bit for the active battler and
 *           advances its pending-count byte while below two.
 */
MATCH void func_800A14B4(void) {
    volatile u8* p;
    u32          slot;
    u32          index;
    u32          count;
    u32          next;

    func_800A3F28();
    p    = &g_BattleActiveBattler;
    slot = LOBU(p[0]);
    if (BATTLER_IS_PLAYER(slot)) {
        g_BattlePartyBattlers[slot].action_flags.volatile_value |= COMBATANT_FLAG_POWER_BOOST;
        index = *p * BATTLE_PARTY_STRIDE;
        count = (&D_80145FC8)[index];
        if (count < 2u) {
            next                 = count + 1;
            (&D_80145FC8)[index] = next;
        }
    } else {
        ENEMY_COMBATANT(slot).action_flags |= COMBATANT_FLAG_POWER_BOOST;
        index = (*p - 3u) * 0x118;
        count = D_801EB744[index];
        if (count < 2u) {
            next              = count + 1;
            D_801EB744[index] = next;
        }
    }
}
