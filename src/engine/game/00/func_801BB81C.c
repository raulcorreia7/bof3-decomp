#include "game_00.h"

MATCH s32 func_801BB81C(s32 first_slot, s32 second_slot) {
    u8  value_a;
    u8  value_b;
    s32 class_a;

    value_a = ((u8*)&g_ScratchPad)[first_slot & BYTE_MASK];
    class_a = value_a & 0xF0;
    if (class_a == 0x20) {
        value_b = ((u8*)&g_ScratchPad)[second_slot & BYTE_MASK];
        if ((value_b & 0xF0) == class_a && value_a != value_b) {
            return 1;
        }
    }
    return 0;
}
