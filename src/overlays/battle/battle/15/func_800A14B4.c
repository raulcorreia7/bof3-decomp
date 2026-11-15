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
    u32          enemy_index;

    Battle_MarkDamageApplied();
    p    = &g_Battle.active_battler;
    slot = LOBU(p[0]);
    if (BATTLER_IS_PLAYER(slot)) {
        g_Game.members[slot].u.turn.action_flags.volatile_value |= COMBATANT_FLAG_POWER_BOOST;
        index = *p * BATTLE_PARTY_STRIDE;
        count = (&D_80145FC8)[index];
        if (count < 2u) {
            next                 = count + 1;
            (&D_80145FC8)[index] = next;
        }
    } else {
        ENEMY_COMBATANT(slot).turn.action_flags.value |= COMBATANT_FLAG_POWER_BOOST;
        enemy_index = *p - 3u;
        count       = g_BattleEnemyBattlers[enemy_index].unk_114;
        if (count < 2u) {
            next                                       = count + 1;
            g_BattleEnemyBattlers[enemy_index].unk_114 = next;
        }
    }
}
