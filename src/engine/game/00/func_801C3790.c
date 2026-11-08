#include "game_00.h"

MATCH s32 func_801C3790(s32 mode_byte) {
    if ((g_Game.flags & 0x400) == 0) {
        return (func_801C364C(0x89, 2, mode_byte & BYTE_MASK) & BYTE_MASK) != 0;
    }
    return 0;
}
