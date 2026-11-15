#include "battle_15.h"

/* resolves the battler's base value, applies the shared damage
 * helper, subtracts the selected record's first halfword and clamps the result
 * at zero.
 */
/* FAKE: _nv weak views avoid the andi and hoist the loads out of the prologue. */
/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
extern u8 D_801CA71B[];

MATCH void func_800A0D64(void) {
    s32         index;
    u8          base_value;
    u8          battler;
    BattleTurn* record;

    index                             = g_Battle.action_id;
    base_value                        = D_801CA71B[4 * (5 * index)];
    g_Battle.target_record->hp_change = Battle_GetActionId(g_BattleActiveBattler_nv, g_BattleTarget_nv, base_value, 0);
    /* FAKE: keeps the record store ahead of the selector read. */
    FAKE_BARRIER();
    battler = g_BattleTarget_nv;
    if (BATTLER_IS_PLAYER(battler)) {
        g_Battle.target_record->hp_change -= g_Game.members[battler].chr.stats.defense;
    } else {
        g_Battle.target_record->hp_change -= ENEMY_COMBATANT(battler).stats.defense;
    }
    record = g_Battle.target_record;
    CLAMP_MIN(record->hp_change, 0);
}
