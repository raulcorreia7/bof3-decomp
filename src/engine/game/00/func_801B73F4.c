#include "game_00.h"

MATCH void func_801B73F4(void) {
    u32 route;

    route = g_Task->direction;
    if (route == FACING_RIGHT) {
        Script_Request(0x38);
    } else {
        Script_Request(0x39);
    }
    g_Game.current->u.field.counter.unsigned_value = 3;
    g_Task->unk_03                                 = 1;
}
