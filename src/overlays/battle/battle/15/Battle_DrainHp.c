#include "battle_15.h"

/* Shows the selected battler's damage step and adjusts the HP bar.
 */
/* func_8009E248 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_DrainHp(void) {
    s32 enemy;
    s16 hp_bar;
    u16 hp;

    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (!(g_Game.members[g_Battle.target].u.turn.damage_flags.volatile_value & BATTLER_DAMAGE_IMMUNE)) {
                hp = g_Game.members[g_Battle.target].chr.hp;
            } else {
                hp = 0;
            }
        } else {
            enemy = g_Battle.target - 3;
            if (g_BattleEnemyBattlers[enemy].turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
                hp = 0;
            } else {
                hp = g_BattleEnemyBattlers[enemy].hp;
            }
        }
        hp_bar                            = hp / 5;
        g_Battle.target_record->hp_change = hp_bar;
        g_Battle.action->unk_08           = 1;
        if (g_Battle.active_battler < 3) {
            if (g_Game.members[g_Battle.active_battler].chr.stats.max_hp < g_Game.members[g_Battle.active_battler].chr.hp + hp_bar) {
                g_Battle.action->unk_08 |= 4;
            }
            Battle_QueueAction((s16)-Char_AddPoints(&g_Game.members[g_Battle.active_battler].chr.hp, g_Game.members[g_Battle.active_battler].chr.stats.max_hp, hp_bar), g_Battle.active_battler);
        } else {
            enemy = g_Battle.active_battler - 3;
            if (g_BattleEnemyBattlers[enemy].stats.max_hp < g_BattleEnemyBattlers[enemy].hp + hp_bar) {
                g_Battle.action->unk_08 |= 4;
            }
            Battle_QueueAction((s16)-Char_AddPoints(&g_BattleEnemyBattlers[enemy].hp, g_BattleEnemyBattlers[enemy].stats.max_hp, hp_bar), g_Battle.active_battler);
        }
        g_Battle.action->unk_08 = 0;
        return;
    }
    g_Battle.target_record->target_flags = 1;
}
#else
INCLUDE_ASM(Battle_DrainHp);
#endif
