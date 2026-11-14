#include "game_00.h"

MATCH void func_801B0DA0(void) {
    Actor* work;
    u8     count;

    g_Game.current->u.field.mode_12B.u8_value = 1;
    work                                      = g_Task;
    count                                     = work->timer;
    if (count == 0) {
        func_801B146C();
    } else {
        work->timer = count - 1;
        Actor_UpdateMovement();
    }
}
