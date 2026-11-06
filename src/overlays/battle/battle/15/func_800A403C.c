#include "battle_15.h"

/* Selection-kind flag table: the signed byte at +3 of each 0x14-byte record. */
extern s8 D_801CA71B[];

MATCH u8 func_800A403C(u8 battler_index) {
    /* FAKE: pin the row index to v1 so the scaled offset keeps v0. */
    MATCH_REG(u16, index, "v1");
    u8 saved;

    func_800A3F28();
    saved = battler_index;
    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) != 0) {
        return 1;
    }
    index = g_BattleActionId;
    func_800A39B4(D_801CA71B[index * 0x14], saved);
    func_800A9BD8(g_BattleTarget);
    return 0;
}
