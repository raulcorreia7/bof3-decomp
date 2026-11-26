#include "game_00.h"

MATCH bool func_801BB6F0(s32 command) {
    u32 value;
    u8  route;

    if ((command & 0xF0) == 0xB0) {
        value = command & 0xF;
        if (value < 6U) {
            route = SELF(Actor)->direction;
            if (value == route) {
                return 1;
            }
        } else if (value == 8) {
            route = SELF(Actor)->direction;
            if ((route == FACING_RIGHT) || (route == FACING_DOWN)) {
                return 1;
            }
        }
    }
    return 0;
}
