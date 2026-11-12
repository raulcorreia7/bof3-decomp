#include "battle_15.h"

/* queues one battler action: allocates a queued slot, points it at
 *           the local or enemy work record, stores the signed magnitude and
 *           sets the action state from the target's flag byte.
 */
/* func_800AAC88 */
MATCH void Battle_QueueAction(s16 amount, u8 battler_index) {
    u8 action_slot;
    u8 target_flags;

    action_slot = Battle_AllocEffect(0, 1);

    g_BattleEffects[action_slot].unk_0B = 0;

    if (battler_index < 3u) {
        g_BattleEffects[action_slot].target.party = &g_Game.members[battler_index];
        target_flags                              = g_Game.members[battler_index].u.turn.target_flags;
    } else {
        g_BattleEffects[action_slot].target.enemy = (EnemyBattler*)g_BattleEnemies + battler_index;
        target_flags                              = ENEMY_COMBATANT(battler_index).turn.target_flags;
    }

    if (amount < 0) {
        g_BattleEffects[action_slot].word_60.target_index = ABS(amount);
        g_BattleEffects[action_slot].unk_27               = 6u;
    } else {
        g_BattleEffects[action_slot].word_60.target_index = amount;
        g_BattleEffects[action_slot].unk_27               = 0u;
    }

    if (!(target_flags & BATTLE_HIT_HP)) {
        g_BattleEffects[action_slot].unk_07 = 4u;
        return;
    }
    if (!(target_flags & BATTLE_HIT_HP_LANDED)) {
        if (target_flags & BATTLE_HIT_HP_MAX) {
            g_BattleEffects[action_slot].unk_27 = 6u;
            g_BattleEffects[action_slot].unk_07 = 2u;
            return;
        }
    }
    if (amount != 0) {
        g_BattleEffects[action_slot].unk_07 = 0u;
        return;
    }
    if (!(target_flags & BATTLE_HIT_HP_LANDED)) {
        g_BattleEffects[action_slot].unk_07 = 3u;
        return;
    }
    g_BattleEffects[action_slot].unk_07 = 0u;
}
