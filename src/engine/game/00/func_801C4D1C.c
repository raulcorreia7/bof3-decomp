#include "game_00.h"

MATCH void func_801C4D1C(void) {
    u32 route;

    route = g_Task->direction_08;
    if (route == FACING_LEFT) {
        Actor_RequestScript(0x3C);
    } else {
        Actor_RequestScript(0x3D);
    }
}
