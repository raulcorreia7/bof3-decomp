#include "battle_15.h"

/* Prepares the selected battler's damage preview: reads the damage cap from the player or enemy row into the
 * 0x801463A0 slot 3, marks the action state, then passes the row limit and the cap to the damage routine after growing
 * the preview when it exceeds the limit. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E500(void) {
    u32  row;
    u16* value;
    u16* limit;

    if (!(Battle_PickAbility(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Game.members[g_Battle.target].u.turn.damage_flags.volatile_value & BATTLER_DAMAGE_IMMUNE) {
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
        row                                  = g_Battle.active_battler;
        if (row < 3) {
            value = &g_Game.members[row].chr.ap;
            limit = &g_Game.members[row].chr.stats.max_ap;
        } else {
            row -= 3;
            value = &g_BattleEnemyBattlers[row].ap;
            limit = &g_BattleEnemyBattlers[row].stats.max_ap;
        }
        if (*limit < *value + g_Battle.target_record->ap_change) {
            g_Battle.action->unk_08 |= 8;
        }
        func_800AAEBC(-Char_AddPoints(value, *limit, g_Battle.target_record->ap_change), g_Battle.active_battler);
        g_Battle.action->unk_08 = 0;
    } else {
        g_Battle.target_record->target_flags = 2;
    }
}
#else
INCLUDE_ASM(func_8009E500);
#endif
