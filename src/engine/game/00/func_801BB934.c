#include "game_00.h"

MATCH bool func_801BB934(s32 first_index, s32 second_index, s8 route_value, s32 expected_value) {
    s32 expected;

    expected = expected_value & BYTE_MASK;
    if (((u8*)&g_ScratchPad)[first_index & BYTE_MASK] == expected) {
        if (((u8*)&g_ScratchPad)[second_index & BYTE_MASK] == expected) {
            return true;
        }
        SELF(Actor)->direction = route_value;
    } else if (((u8*)&g_ScratchPad)[second_index & BYTE_MASK] == expected) {
        SELF(Actor)->direction = (route_value ^ 0x4);
    }
    return false;
}
