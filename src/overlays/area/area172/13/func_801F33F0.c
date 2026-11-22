#include "area172_13.h"

MATCH void func_801F33F0(void) {
    Actor* work;
    Actor* actor;

    work        = TASK(Actor);
    work->timer = 32;
    actor       = TASK(Actor);
    work->vx    = 0;
    actor->header.mode++;
    g_AreaDrawFlags = 0;
}
