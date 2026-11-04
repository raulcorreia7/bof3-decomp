#include "battle_15.h"

/* allocates a queued battle-action slot, binds it to a battler,
 * records the signed target index, and selects the action mode from the
 * battler's status flags.
 */

MATCH void func_800AAEBC(s16 target_index, u8 battler_index) {
    u8  action_slot;
    u8  target_flags;
    s32 enemy;

    action_slot                         = (u8)Battle_AllocEffect(0, 1);
    g_BattleEffects[action_slot].unk_0B = 1u;

    if (BATTLER_IS_PLAYER(battler_index)) {
        g_BattleEffects[action_slot].work_74.party = &g_BattlePartyBattlers[battler_index];
        target_flags                               = g_BattlePartyBattlers[battler_index].unk_120;
    } else {
        enemy                                      = (s32)battler_index - 3;
        g_BattleEffects[action_slot].work_74.enemy = (EnemyBattler*)g_BattleEnemies + battler_index;
        target_flags                               = D_801EB72C[((u32)enemy * BATTLE_ENEMY_STRIDE)];
    }

    if (target_index < 0) {
        g_BattleEffects[action_slot].word_60.target_index = target_index >= 0 ? target_index : -target_index;
        g_BattleEffects[action_slot].unk_27               = 1u;
    } else {
        g_BattleEffects[action_slot].word_60.target_index = target_index;
        g_BattleEffects[action_slot].unk_27               = 2u;
    }

    if (!(target_flags & 0x2u)) {
        g_BattleEffects[action_slot].unk_07 = 4u;
        return;
    }
    if (target_flags & 0x20u) {
        g_BattleEffects[action_slot].unk_07 = 0u;
    } else if (target_flags & 0x8u) {
        g_BattleEffects[action_slot].unk_27 = 1u;
        g_BattleEffects[action_slot].unk_07 = 2u;
        return;
    } else {
        g_BattleEffects[action_slot].unk_07 = 0u;
    }
}
