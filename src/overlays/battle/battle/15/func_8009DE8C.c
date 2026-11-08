#include "battle_15.h"

/* Active battle-selection record head (0x80146394). */

MATCH void func_8009DE8C(void) {
    BattleSelectionContext* ctx;
    u32                     sel;
    u16                     value;
    s64                     negated;

    ctx = (BattleSelectionContext*)&g_Battle.target;
    sel = ctx->sel;
    if (BATTLER_IS_PLAYER(sel)) {
        g_Battle.target_record->hp_change = -g_Game.members[sel].chr.stats.max_hp;
    } else {
        value = ENEMY_COMBATANT(sel).stats.max_hp;
        if (value == 0xFFFFu) {
            g_Battle.target_record->hp_change = -1;
            ENEMY_COMBATANT(ctx->sel).turn.target_flags |= BATTLE_HIT_HP_MAX;
            return;
        }
        /* Negation materialized first, matching the original's evaluation order. */
        /* FAKE: scheduler rows j-target/negu/tail need s64 temp;
         * plain/s32/s16/order/hi-lo ladders miss. */
        negated = (g_Battle.target_record->hp_change = -value);
    }
}
