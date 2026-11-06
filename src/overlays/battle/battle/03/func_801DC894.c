#include "battle_03.h"

/* lets the damage through, or blocks it and clears bit 0x10 of the target's flags,
 * by the attacker's status 0x8 roll, the target's 0x4 roll and the D_801EC324 percent roll.
 */
MATCH u32 func_801DC894(s16 damage, u8 attacker, u8 target) {
    u8 threshold;

    if (g_BattleState & BATTLE_STATE_CRITICAL) {
        return damage;
    }
    if (BATTLER_IS_PLAYER(attacker)) {
        if (HAS_STATUS(g_BattlePartyBattlers[attacker], STATUS_BLIND) && (rand() & 2)) {
            ENEMY_COMBATANT(target).target_flags &= ~0x10;
            return 0;
        }
    } else if ((ENEMY_COMBATANT(attacker).status & STATUS_BLIND) && (rand() & 2)) {
        ENEMY_COMBATANT(target).target_flags &= ~0x10;
        return 0;
    }
    if (attacker < 3 && (g_BattlePartyBattlers[attacker].action_flags.value & 0x100)) {
        return damage;
    }
    if ((ENEMY_COMBATANT(target).event_flags & 4) && (rand() & 2)) {
        ENEMY_COMBATANT(target).target_flags &= ~0x10;
        return 0;
    }
    if (!BATTLER_IS_PLAYER(attacker)) {
        return damage;
    }
    threshold = D_801EC324;
    if (rand() % 100 < threshold) {
        return damage;
    }
    ENEMY_COMBATANT(target).target_flags &= ~0x10;
    return 0;
}
