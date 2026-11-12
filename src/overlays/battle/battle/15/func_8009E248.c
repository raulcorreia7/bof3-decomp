#include "battle_15.h"

/* Shows the selected battler's damage step and adjusts the HP bar.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E248(void) {
    s32 id;
    s32 enemy;
    s16 hp_bar;
    u16 hp;

    id = g_Battle.active_battler;
    if (!(func_800A3A10(id, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (!(g_Game.members[g_Battle.target].u.turn.damage_flags.volatile_value & COMBATANT_FLAG_DAMAGE_IMMUNE)) {
                hp = g_Game.members[g_Battle.target].chr.hp;
            } else {
                hp = 0;
            }
        } else {
            enemy = g_Battle.target - 3;
            if (g_BattleEnemyBattlers[enemy].turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
                hp = 0;
            } else {
                hp = g_BattleEnemyBattlers[enemy].hp;
            }
        }
        hp_bar                            = hp / 5;
        g_Battle.target_record->hp_change = hp_bar;
        g_Battle.action->unk_08           = 1;
        if (id < 3) {
            if (g_Game.members[id].chr.stats.max_hp < g_Game.members[id].chr.hp + hp_bar) {
                g_Battle.action->unk_08 |= 4;
            }
            Battle_QueueAction((s16)-Char_AddPoints(&g_Game.members[id].chr.hp, g_Game.members[id].chr.stats.max_hp, hp_bar), id);
        } else {
            enemy = id - 3;
            if (g_BattleEnemyBattlers[enemy].stats.max_hp < g_BattleEnemyBattlers[enemy].hp + hp_bar) {
                g_Battle.action->unk_08 |= 4;
            }
            Battle_QueueAction((s16)-Char_AddPoints(&g_BattleEnemyBattlers[enemy].hp, g_BattleEnemyBattlers[enemy].stats.max_hp, hp_bar), id);
        }
        g_Battle.action->unk_08 = 0;
        return;
    }
    g_Battle.target_record->target_flags = 1;
}
#else
INCLUDE_ASM(func_8009E248);
#endif
