#include "battle_15.h"

MATCH bool func_800AA8A4(s32 battler_index) {
    s32 index;
    u8* row;

    index = 0;
    row   = g_BattlePartyBattlers[(battler_index & 0xFF)].chr.abilities.skill;
    for (; (u32)(index & 0xFF) < 10; index++) {
        if (row[index & 0xFF] == 0) {
            return false;
        }
    }
    return true;
}
