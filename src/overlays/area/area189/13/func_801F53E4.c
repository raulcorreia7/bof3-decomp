#include "area189_13.h"

MATCH void func_801F53E4(void) {
    Actor* work;

    g_GameState->mode_12B.u8_value = 1;
    work                           = g_Task;
    if (work->timer == 0) {
        func_801F5600();
    } else {
        work->timer = work->timer - 1;
        func_801F559C();
    }
}
