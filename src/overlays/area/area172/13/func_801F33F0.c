#include "area172_13.h"

MATCH void func_801F33F0(void) {
    Actor* work;
    Actor* actor;

    work        = SELF(Actor);
    work->timer = 32;
    actor       = SELF(Actor);
    work->vx    = 0;
    actor->header.mode++;
    g_AreaDrawFlags = 0;
}
