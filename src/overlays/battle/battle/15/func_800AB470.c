#include "battle_15.h"

MATCH bool func_800AB470(u8 battler_index) {
    u16 value;

    value = g_Game.members[battler_index].u.turn.command.id;
    if (value == 0x4C)
        return 1;
    if (value == 0x4D)
        return 1;
    if (value != 0xB4)
        return value == 0xB5;
    return 1;
}
