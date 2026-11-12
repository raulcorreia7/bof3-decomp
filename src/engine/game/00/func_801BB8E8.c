#include "game_00.h"

MATCH void func_801BB8E8(u8 arg_a, u8 arg_b, u8 arg_c) {
    Actor* work;
    u8     current;

    work    = g_Task;
    current = work->direction_08;

    if (current & 0x1) {
        return;
    }

    if (current == arg_a) {
        work->direction_08 = arg_c;
    } else if (current == arg_b) {
        work->direction_08 = arg_c;
    } else {
        work->direction_08 = arg_c ^ 0x4;
    }
}
