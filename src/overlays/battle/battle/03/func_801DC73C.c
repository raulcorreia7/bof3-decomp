#include "battle_03.h"

/* Byte-displacement views over the local-work array (stride 0x140) and the
 * enemy-work array (stride 0x118). */

/* conditionally zeroes one local status bit after a random gate,
 * otherwise passing through the signed damage value unchanged.
 */
MATCH u32 func_801DC73C(s16 damage, u32 battler_index, u32 target_index) {
    u16 flags;
    s32 threshold;
    u32 index;
    /* FAKE: enemy-index temp in v0; clean C leaves the v0/v1 tie-break
     * swapped (retail scales in v1, keeps the index in v0). */
    MATCH_FAKE_PIN(u32, enemy_index, "v0");

    index = target_index;
    if ((g_BattleState & BATTLE_STATE_CRITICAL) != 0u) {
        return (s32)damage;
    }

    battler_index &= BYTE_MASK;
    if (BATTLER_IS_PLAYER(battler_index)) {
        flags = g_BattlePartyBattlers[battler_index].chr.status;
    } else {
        /* enemy rows share the flag test below */
        goto enemy;
    }

have_flags:
    if ((flags & STATUS_BLIND) == 0u) {
        /* no suppression flag: keep the damage value */
        goto after_enemy;
    }
    if (RANDOM_MASK(2u) == 0u) {
        /* random pass: keep the damage value */
        goto after_enemy;
    }
    /* failures fall through to the shared clear */
    goto clear;

enemy:
    enemy_index = battler_index - 3u;
    flags       = g_BattleEnemyBattlers[enemy_index].status;
    /* run the shared flag test */
    goto have_flags;

after_enemy:
    threshold = D_801EC303;
    if (threshold >= rand() % 100) {
        /* threshold passed: clear the status instead */
        goto clear;
    }
    return (s32)damage;

clear:
    g_BattlePartyBattlers[index & BYTE_MASK].u.turn.target_flags &= ~BATTLE_HIT_HP_LANDED;
    return 0u;
}
