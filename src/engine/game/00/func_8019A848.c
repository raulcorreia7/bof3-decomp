#include "game_00.h"

MATCH void func_8019A848(void) {
    Actor* work;

    D_801C80C8[TASK(Actor)->unk_06]();

    work = TASK(Actor);
    work->screen_x += work->vx;
    work->screen_y -= work->vy;
}
