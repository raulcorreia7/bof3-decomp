#include "battle_15.h"

/* resolves the battler's base value, applies the shared damage
 * helper, subtracts the selected record's first halfword and clamps the result
 * at zero.
 */
/* FAKE: _nv weak views avoid the andi and hoist the loads out of the prologue. */
/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */
extern u8           D_801CA71B[];
extern volatile u16 D_80145F26[][160];

MATCH void func_800A0D64(void) {
    s32  index;
    u8   base_value;
    u8   battler;
    s16* record;

    index                   = g_BattleActionId;
    base_value              = D_801CA71B[4 * (5 * index)];
    g_BattleTargetRecord[2] = func_800A2880(g_BattleActiveBattler_nv, g_BattleTarget_nv, base_value, 0);
    /* FAKE: keeps the record store ahead of the selector read. */
    MATCH_BARRIER();
    battler = g_BattleTarget_nv;
    if (BATTLER_IS_PLAYER(battler)) {
        ((s16*)g_BattleTargetRecord)[2] -= D_80145F26[battler][0];
    } else {
        ((s16*)g_BattleTargetRecord)[2] -= D_801EB6D6[battler - 3u][0];
    }
    record = (s16*)g_BattleTargetRecord;
    if (record[2] < 0) {
        record[2] = 0;
    }
}
