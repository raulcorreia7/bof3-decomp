#include "battle_15.h"

/* Takes a fifth of the target's HP and gives it to the active battler. */
/* func_8009E248 */
MATCH void Battle_DrainHp(void) {
    s16 gained;

    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Game.members[g_Battle.target].u.turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
                g_Battle.target_record->hp_change = 0;
            } else {
                g_Battle.target_record->hp_change = g_Game.members[g_Battle.target].chr.hp / 5;
            }
        } else if (ENEMY_COMBATANT(g_Battle.target).turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
            g_Battle.target_record->hp_change = 0;
        } else {
            g_Battle.target_record->hp_change = ENEMY_COMBATANT(g_Battle.target).hp / 5;
        }
        g_Battle.action->unk_08 = 1;
        if (g_Battle.active_battler < 3) {
            if (g_Game.members[g_Battle.active_battler].chr.stats.max_hp < g_Game.members[g_Battle.active_battler].chr.hp + g_Battle.target_record->hp_change) {
                g_Battle.action->unk_08 |= 4;
            }
            gained = Char_AddPoints(&g_Game.members[g_Battle.active_battler].chr.hp, g_Game.members[g_Battle.active_battler].chr.stats.max_hp, g_Battle.target_record->hp_change);
        } else {
            if (ENEMY_COMBATANT(g_Battle.active_battler).stats.max_hp < ENEMY_COMBATANT(g_Battle.active_battler).hp + g_Battle.target_record->hp_change) {
                g_Battle.action->unk_08 |= 4;
            }
            gained = Char_AddPoints(&ENEMY_COMBATANT(g_Battle.active_battler).hp, ENEMY_COMBATANT(g_Battle.active_battler).stats.max_hp, g_Battle.target_record->hp_change);
        }
        Battle_QueueAction(-gained, g_BattleActiveBattler_nv);
        g_Battle.action->unk_08 = 0;
        return;
    }
    g_Battle.target_record->target_flags = 1;
}
