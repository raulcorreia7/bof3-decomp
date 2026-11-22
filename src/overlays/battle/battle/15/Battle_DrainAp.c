#include "battle_15.h"

/* Takes a fifth of the target's AP and gives it to the active battler. */
/* func_8009E500 */
MATCH void Battle_DrainAp(void) {
    s16 gained;

    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Game.members[g_Battle.target].u.turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
                g_Battle.target_record->ap_change = 0;
            } else {
                g_Battle.target_record->ap_change = g_Game.members[g_Battle.target].chr.ap / 5;
            }
        } else if (ENEMY_COMBATANT(g_Battle.target).turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
            g_Battle.target_record->ap_change = 0;
        } else {
            g_Battle.target_record->ap_change = ENEMY_COMBATANT(g_Battle.target).ap / 5;
        }
        g_Battle.action->unk_08              = 2;
        g_Battle.target_record->target_flags = 2;
        if (g_Battle.active_battler < 3) {
            if (g_Game.members[g_Battle.active_battler].chr.stats.max_ap < g_Game.members[g_Battle.active_battler].chr.ap + g_Battle.target_record->ap_change) {
                g_Battle.action->unk_08 |= 8;
            }
            gained = Char_AddPoints(&g_Game.members[g_Battle.active_battler].chr.ap, g_Game.members[g_Battle.active_battler].chr.stats.max_ap, g_Battle.target_record->ap_change);
        } else {
            if (ENEMY_COMBATANT(g_Battle.active_battler).stats.max_ap < ENEMY_COMBATANT(g_Battle.active_battler).ap + g_Battle.target_record->ap_change) {
                g_Battle.action->unk_08 |= 8;
            }
            gained = Char_AddPoints(&ENEMY_COMBATANT(g_Battle.active_battler).ap, ENEMY_COMBATANT(g_Battle.active_battler).stats.max_ap, g_Battle.target_record->ap_change);
        }
        func_800AAEBC(-gained, g_BattleActiveBattler_nv);
        g_Battle.action->unk_08 = 0;
        return;
    }
    g_Battle.target_record->target_flags = 2;
}
