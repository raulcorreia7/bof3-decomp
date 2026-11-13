#include "game_00.h"

MATCH bool func_801BB934(s32 first_index, s32 second_index, s8 route_value, s32 expected_value) {
    s32 expected;

    expected = expected_value & BYTE_MASK;
    if (((u8*)&D_1F800000)[first_index & BYTE_MASK] == expected) {
        if (((u8*)&D_1F800000)[second_index & BYTE_MASK] == expected) {
            return true;
        }
        g_Task->direction_08 = route_value;
    } else if (((u8*)&D_1F800000)[second_index & BYTE_MASK] == expected) {
        g_Task->direction_08 = (route_value ^ 0x4);
    }
    return false;
}
