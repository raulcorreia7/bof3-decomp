#include "battle_15.h"

/* Prepares the selected battler's damage preview: reads the damage cap from the player or enemy row into the
 * 0x801463A0 slot 3, marks the action state, then passes the row limit and the cap to the damage routine after growing
 * the preview when it exceeds the limit. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E500(void) {
    s16 delta;
    u16 limit;
    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Game.members[g_Battle.target].u.turn.damage_flags.volatile_value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
                g_Battle.target_record->ap_change = 0;
            } else {
                g_Battle.target_record->ap_change = g_Game.members[g_Battle.target].chr.ap / 5;
            }
        } else if (ENEMY_COMBATANT(g_Battle.target).turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            g_Battle.target_record->ap_change = 0;
        } else {
            g_Battle.target_record->ap_change = ENEMY_COMBATANT(g_Battle.target).ap / 5;
        }
        g_Battle.action->unk_08              = 2;
        g_Battle.target_record->target_flags = 2;
        delta                                = g_Battle.target_record->ap_change;
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            limit = g_Game.members[g_Battle.active_battler].chr.stats.max_ap;
            if (limit < g_Game.members[g_Battle.active_battler].chr.ap + delta) {
                g_Battle.action->unk_08 |= 8;
            }
            func_800AAEBC(-Char_AddPoints(&g_Game.members[g_Battle.active_battler].chr.ap, limit, delta), g_Battle.active_battler);
        } else {
            limit = ENEMY_COMBATANT(g_Battle.active_battler).stats.max_ap;
            if (limit < ENEMY_COMBATANT(g_Battle.active_battler).ap + delta) {
                g_Battle.action->unk_08 |= 8;
            }
            func_800AAEBC(-Char_AddPoints(&ENEMY_COMBATANT(g_Battle.active_battler).ap, limit, delta), g_Battle.active_battler);
        }
        g_Battle.action->unk_08 = 0;
    } else {
        g_Battle.target_record->target_flags = 2;
    }
}
#else
INCLUDE_ASM(func_8009E500);
#endif
