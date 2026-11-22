#include "area172_13.h"

MATCH void func_801F33F0(void) {
    Actor* work;
    Actor* step;

    work        = TASK(Actor);
    work->timer = 32;
    step        = TASK(Actor);
    work->vx    = 0;
    step->header.mode++;
    g_AreaDrawFlags = 0;
}
