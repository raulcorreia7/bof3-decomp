#include "battle_03.h"

/* Arms a queued action for every live battler: copies the battler's work
 * record into the next free queued slot and seeds the slot's handler-index bytes.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801DE1D4(void) {
    u8  index;
    u32 slot;

    for (index = 0; index < COMBATANT_COUNT; index++) {
        if (index < 3) {
            if (!ACTOR_IN_USE(g_Game.members[index])) {
                continue;
            }
            if (g_Game.members[index].turn.action_flags.value & COMBATANT_FLAG_MODE_HANDLER_ACTION) {
                continue;
            }
            slot = Battle_AllocEffect(0, 7);
            memcpy(&g_BattleEffects[(u8)slot], &g_Game.members[index], 0x74);
            g_BattleEffects[(u8)slot].target.party  = &g_Game.members[index];
            g_Task                                  = &g_Game.members[index];
            g_BattleEffects[(u8)slot].handler_index = 7;
            g_BattleEffects[(u8)slot].unk_06        = 0;
            g_BattleEffects[(u8)slot].header.mode   = 0;
            g_BattleEffects[(u8)slot].header.step   = 0;
            g_BattleEffects[(u8)slot].unk_29        = 3;
            g_BattleEffects[(u8)slot].unk_5C        = 0;
            g_BattleEffects[(u8)slot].unk_5D        = 0;
            g_BattleEffects[(u8)slot].unk_5F        = 0;
            g_BattleEffects[(u8)slot].unk_5E        = 0;
        } else {
            if (Battle_SlotIsBlocked(index) & BYTE_MASK) {
                continue;
            }
            if (ENEMY_COMBATANT(index).turn.action_flags.value & COMBATANT_FLAG_MODE_HANDLER_ACTION) {
                continue;
            }
            slot = Battle_AllocEffect(0, 7);
            memcpy(&g_BattleEffects[(u8)slot], &ENEMY_COMBATANT(index), 0x74);
            g_BattleEffects[(u8)slot].target.enemy = (EnemyBattler*)g_BattleEnemies + index;
            TASK_SET((g_BattleEnemies + index * 0x118));
            g_BattleEffects[(u8)slot].handler_index = 7;
            g_BattleEffects[(u8)slot].unk_06        = 0;
            g_BattleEffects[(u8)slot].header.mode   = 0;
            g_BattleEffects[(u8)slot].header.step   = 0;
            g_BattleEffects[(u8)slot].unk_29        = 3;
            g_BattleEffects[(u8)slot].unk_5C        = 0;
            g_BattleEffects[(u8)slot].unk_5D        = 0;
            g_BattleEffects[(u8)slot].unk_5F        = 0;
            g_BattleEffects[(u8)slot].unk_5E        = 0;
        }
    }
}
#else
INCLUDE_ASM(func_801DE1D4);
#endif
