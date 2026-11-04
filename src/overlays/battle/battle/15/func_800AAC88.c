#include "battle_15.h"

/* queues one battler action: allocates a queued slot, points it at
 *           the local or enemy work record, stores the signed magnitude and
 *           sets the action state from the target's flag byte.
 */
MATCH void func_800AAC88(s16 amount, u8 battler_index) {
    u8  action_slot;
    u8  target_flags;
    s32 enemy;

    action_slot = (u8)Battle_AllocEffect(0, 1);

    D_801EC33B[action_slot * BATTLE_EFFECT_STRIDE] = 0;

    if (battler_index < 3u) {
        g_BattleEffects[action_slot].target.party = &g_BattlePartyBattlers[battler_index];
        target_flags                              = g_BattlePartyBattlers[battler_index].unk_120;
    } else {
        enemy                                     = (s32)battler_index - 3;
        g_BattleEffects[action_slot].target.enemy = (EnemyBattler*)g_BattleEnemies + battler_index;
        target_flags                              = D_801EB72C[((u32)enemy * BATTLE_ENEMY_STRIDE)];
    }

    if (amount < 0) {
        *(u32*)(D_801EC390 + action_slot * BATTLE_EFFECT_STRIDE) = ABS(amount);
        D_801EC357[action_slot * BATTLE_EFFECT_STRIDE]           = 6u;
    } else {
        *(u32*)(D_801EC390 + action_slot * BATTLE_EFFECT_STRIDE) = amount;
        D_801EC357[action_slot * BATTLE_EFFECT_STRIDE]           = 0u;
    }

    if (!(target_flags & 0x1u)) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 4u;
        return;
    }
    if (!(target_flags & 0x10u)) {
        if (target_flags & 0x4u) {
            D_801EC357[action_slot * BATTLE_EFFECT_STRIDE] = 6u;
            D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 2u;
            return;
        }
    }
    if (amount != 0) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 0u;
        return;
    }
    if (!(target_flags & 0x10u)) {
        D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 3u;
        return;
    }
    D_801EC337[action_slot * BATTLE_EFFECT_STRIDE] = 0u;
}
