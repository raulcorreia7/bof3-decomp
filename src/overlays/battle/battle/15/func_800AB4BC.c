#include "battle_15.h"

/* @returns 1 if the value at the kind_index row in D_80145FAA equals 0xE or
 * 0x128.
 */
MATCH s32 func_800AB4BC(s32 kind_index) {
    u16 value;

    value = g_BattlePartyBattlers[kind_index & BYTE_MASK].turn.command.id;
    if (value != 0xE)
        return value == 0x128;
    return 1;
}
