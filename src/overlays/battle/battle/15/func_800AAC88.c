#include "battle_15.h"

/* queues one battler action: allocates a queued slot, points it at
 *           the local or enemy work record, stores the signed magnitude and
 *           sets the action state from the target's flag byte.
 */
MATCH void func_800AAC88(s16 amount, u8 battler_index) {
    u8 action_slot;
    u8 target_flags;

    action_slot = Battle_AllocEffect(0, 1);

    D_801EC33B[action_slot * BATTLE_EFFECT_STRIDE] = 0;

    if (battler_index < 3u) {
        g_BattleEffects[action_slot].target.party = &g_BattlePartyBattlers[battler_index];
        target_flags                              = g_BattlePartyBattlers[battler_index].turn.target_flags;
    } else {
        g_BattleEffects[action_slot].target.enemy = (EnemyBattler*)g_BattleEnemies + battler_index;
        target_flags                              = ENEMY_COMBATANT(battler_index).turn.target_flags;
    }

    if (amount < 0) {
        *(u32*)(D_801EC390 + action_slot * BATTLE_EFFECT_STRIDE) = ABS(amount);
        D_801EC357[action_slot * BATTLE_EFFECT_STRIDE]           = 6u;
    } else {
        *(u32*)(D_801EC390 + action_slot * BATTLE_EFFECT_STRIDE) = amount;
        D_801EC357[action_slot * BATTLE_EFFECT_STRIDE]           = 0u;
    }

    if (!(target_flags & BATTLE_HIT_HP)) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 4u;
        return;
    }
    if (!(target_flags & BATTLE_HIT_HP_LANDED)) {
        if (target_flags & BATTLE_HIT_HP_MAX) {
            D_801EC357[action_slot * BATTLE_EFFECT_STRIDE] = 6u;
            D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 2u;
            return;
        }
    }
    if (amount != 0) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 0u;
        return;
    }
    if (!(target_flags & BATTLE_HIT_HP_LANDED)) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 3u;
        return;
    }
    D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 0u;
}
