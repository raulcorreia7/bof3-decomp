#include "battle_15.h"

MATCH bool func_800AA8A4(s32 battler_index) {
    s32 idx;
    u8* row;

    idx = 0;
    row = g_BattlePartyBattlers[(battler_index & BYTE_MASK)].chr.abilities.skill;
    for (; (u32)(idx & BYTE_MASK) < 10; idx++) {
        if (row[idx & BYTE_MASK] == 0) {
            return false;
        }
    }
    return true;
}
