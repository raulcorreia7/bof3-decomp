#include "battle_15.h"

/* Prepares the selected battler's damage preview. */
/* nonmatching unmeasured: tried frame 0x28 vs 0x18: the cached delta/limit locals spill while the retail keeps them in
 * registers; branch layout now bne to the tail store. resume: drive both halves from one u32 row index and pass the row
 * addresses as non-volatile u16 pointers. */
#ifdef NON_MATCHING
NON_MATCHING void func_8009E500(void) {
    s16 delta;
    u16 limit;
    if (!(func_800A3A10(g_Battle.active_battler, g_Battle.target) & BYTE_MASK)) {
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
            func_800AAEBC(-Char_AddPoints(&g_Game.members[g_Battle.active_battler].chr.ap, limit, delta),
                          g_Battle.active_battler);
        } else {
            limit = ENEMY_COMBATANT(g_Battle.active_battler).stats.max_ap;
            if (limit < ENEMY_COMBATANT(g_Battle.active_battler).ap + delta) {
                g_Battle.action->unk_08 |= 8;
            }
            func_800AAEBC(-Char_AddPoints(&ENEMY_COMBATANT(g_Battle.active_battler).ap, limit, delta),
                          g_Battle.active_battler);
        }
        g_Battle.action->unk_08 = 0;
    } else {
        g_Battle.target_record->target_flags = 2;
    }
}
#else
INCLUDE_ASM(func_8009E500);
#endif
