#include "game_00.h"

MATCH s32 func_801BB6F0(s32 command) {
    u32 value;
    u8  route;

    if ((command & 0xF0) == 0xB0) {
        value = command & 0xF;
        if (value < 6U) {
            route = g_SpadWork->direction_08;
            if (value == route) {
                return 1;
            }
        } else if (value == 8) {
            route = g_SpadWork->direction_08;
            if ((route == 3) || (route == 5)) {
                return 1;
            }
        }
    }
    return 0;
}
