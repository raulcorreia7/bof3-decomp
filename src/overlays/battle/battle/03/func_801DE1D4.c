#include "battle_03.h"

/* Arms a queued action for every live battler: copies the battler's work
 * record into the next free queued slot and seeds the slot's handler-index bytes.
 */
MATCH void func_801DE1D4(void) {
    u8  index;
    u32 slot;
    s32 enemy;

    for (index = 0; index < COMBATANT_COUNT; index++) {
        if (index < 3) {
            if (!ACTOR_IN_USE(g_Game.members[index])) {
                continue;
            }
            if (g_Game.members[index].u.turn.action_flags.value & BATTLER_ACTION_OWN_MODE) {
                continue;
            }
            slot                                          = Battle_AllocEffect(0, 7);
            *(BattleWorkImage*)&g_BattleEffects[(u8)slot] = *(BattleWorkImage*)&g_Game.members[index];
            (&g_BattleEffects[(u8)slot])->target.party    = &g_Game.members[index];
            SELF_SET(&g_Game.members[index]);
        } else {
            if (Battle_SlotIsBlocked(index)) {
                continue;
            }
            enemy = index - 3;
            if (g_BattleEnemyBattlers[enemy].turn.action_flags.value & BATTLER_ACTION_OWN_MODE) {
                continue;
            }
            slot                                          = Battle_AllocEffect(0, 7);
            *(BattleWorkImage*)&g_BattleEffects[(u8)slot] = *(BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
            (&g_BattleEffects[(u8)slot])->target.enemy    = (EnemyBattler*)g_BattleEnemies + index;
            SELF_SET((EnemyBattler*)g_BattleEnemies + index);
        }
        (&g_BattleEffects[(u8)slot])->effect_type = 7;
        (&g_BattleEffects[(u8)slot])->unk_06      = 0;
        (&g_BattleEffects[(u8)slot])->header.mode = 0;
        (&g_BattleEffects[(u8)slot])->header.step = 0;
        (&g_BattleEffects[(u8)slot])->unk_29      = 3;
        (&g_BattleEffects[(u8)slot])->unk_5C      = 0;
        (&g_BattleEffects[(u8)slot])->unk_5D      = 0;
        (&g_BattleEffects[(u8)slot])->unk_5F      = 0;
        (&g_BattleEffects[(u8)slot])->unk_5E      = 0;
    }
}
