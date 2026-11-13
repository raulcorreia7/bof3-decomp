#include "battle_15.h"

/* Selection-kind flag table: the signed byte at +3 of each 0x14-byte record. */
extern s8 D_801CA71B[];

MATCH u8 func_800A40D0(u8 battler_index) {
    u16 index;

    if (Battle_PickAbility(g_BattleActiveBattler, g_BattleTarget) != 0) {
        return true;
    }
    index = g_BattleActionId;
    Battle_SetTarget(D_801CA71B[index * 0x14], battler_index);
    Battle_RescaleStats(g_Battle.target);
    return false;
}
