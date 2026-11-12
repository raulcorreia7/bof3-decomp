#include "game_00.h"

MATCH s32 func_801BB7B0(s32 selector) {
    s32 value;

    value = ((u8*)&D_1F800000)[selector & BYTE_MASK] & 0xF;
    switch (value) {
        case 0x0F:
            return 2;
        case 2:
            return 5;
        case 1:
            return 2;
        case 3:
            return 4;
        default:
            return 4;
    }
}
