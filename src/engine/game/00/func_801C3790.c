#include "game_00.h"

MATCH s32 func_801C3790(s32 mode_byte) {
    if ((g_GameFlags & 0x400) == 0) {
        return (func_801C364C(0x89, 2, mode_byte & 0xFF) & 0xFF) != 0;
    }
    return 0;
}
