#include "battle_15.h"

MATCH bool func_800AA8A4(s32 battler_index) {
    s32 index;
    u8* row;

    index = 0;
    row   = g_Game.members[(battler_index & BYTE_MASK)].chr.abilities.skill;
    for (; (u32)(index & BYTE_MASK) < 10; index++) {
        if (row[index & BYTE_MASK] == 0) {
            return false;
        }
    }
    return true;
}
