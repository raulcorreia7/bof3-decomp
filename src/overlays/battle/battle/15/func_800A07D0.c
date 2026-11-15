#include "battle_15.h"

/* Enemy work halfword pair at +0x84 (stride 0x118, indexed by slot - 3). */

/* doubles the two selected enemy-row halfwords and clamps them to
 * 0xFFFF; it re-reads the selector before storing the second result.
 */
MATCH void func_800A07D0(void) {
    BattleSelectionContext* ctx;
    s32                     first_doubled;
    s32                     second_doubled;
    u16                     first;
    u16                     second;
    u32                     index;

    Battle_MarkDamageApplied();
    ctx           = (BattleSelectionContext*)&g_Battle.target;
    index         = ctx->sel - 3u;
    first         = g_BattleEnemyBattlers[index].zenny;
    second        = g_BattleEnemyBattlers[index].exp;
    first_doubled = first * 2;
    first         = first_doubled;
    if (first_doubled > 0xFFFF) {
        first = 0xFFFF;
    }
    second_doubled = second * 2;
    second         = second_doubled;
    if (second_doubled > 0xFFFF) {
        second = 0xFFFF;
    }
    g_BattleEnemyBattlers[index].zenny       = first;
    g_BattleEnemyBattlers[ctx->sel - 3u].exp = second;
}
