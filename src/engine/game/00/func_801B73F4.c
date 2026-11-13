#include "game_00.h"

MATCH void func_801B73F4(void) {
    u32 route;

    route = g_Task->direction_08;
    if (route == FACING_RIGHT) {
        Actor_RequestScript(0x38);
    } else {
        Actor_RequestScript(0x39);
    }
    g_Game.current->u.field.counter_11C.u8_value = 3;
    g_Task->unk_03                               = 1;
}
