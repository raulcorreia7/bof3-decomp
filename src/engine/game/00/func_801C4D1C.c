#include "game_00.h"

MATCH void func_801C4D1C(void) {
    u32 route;

    route = g_Task->direction;
    if (route == FACING_LEFT) {
        Script_Request(0x3C);
    } else {
        Script_Request(0x3D);
    }
}
