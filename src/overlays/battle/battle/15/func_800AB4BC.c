#include "battle_15.h"

/* @returns 1 if the value at the type_index row in D_80145FAA equals 0xE or
 * 0x128.
 */
MATCH bool func_800AB4BC(s32 type_index) {
    u16 value;

    value = g_Game.members[type_index & BYTE_MASK].u.turn.command.id;
    if (value != 0xE)
        return value == 0x128;
    return 1;
}
