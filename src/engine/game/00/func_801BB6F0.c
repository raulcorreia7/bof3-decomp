#include "game_00.h"

MATCH bool func_801BB6F0(s32 command) {
    u32 value;
    u8  route;

    if ((command & 0xF0) == 0xB0) {
        value = command & 0xF;
        if (value < 6U) {
            route = g_Task->direction_08;
            if (value == route) {
                return 1;
            }
        } else if (value == 8) {
            route = g_Task->direction_08;
            if ((route == FACING_RIGHT) || (route == FACING_DOWN)) {
                return 1;
            }
        }
    }
    return 0;
}
