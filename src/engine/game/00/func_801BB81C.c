#include "game_00.h"

MATCH s32 func_801BB81C(s32 first_slot, s32 second_slot) {
    u8  value_a;
    u8  value_b;
    s32 class_a;
    /* FAKE: result pinned to v0; allocator picks v1 without it. */
    MATCH_REG(s32, result, "v0");

    value_a = ((u8*)&D_1F800000)[first_slot & BYTE_MASK];
    class_a = value_a & 0xF0;
    result  = 0;
    if (class_a == 0x20) {
        value_b = ((u8*)&D_1F800000)[second_slot & BYTE_MASK];
        if ((value_b & 0xF0) == class_a) {
            result = value_a ^ value_b;
            result = result != 0;
        }
    }
    return result;
}
