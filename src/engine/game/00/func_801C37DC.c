#include "game_00.h"

MATCH bool func_801C37DC(s32 mode_byte) {
    if ((g_Game.flags & 0x400) == 0) {
        return (Party_StartFloorDamage(0x8A, 1, mode_byte & BYTE_MASK) & BYTE_MASK) != 0;
    }
    return 0;
}
