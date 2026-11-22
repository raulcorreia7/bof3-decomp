#include "area173_14.h"

MATCH void func_801F4298(void) {
    Actor* work;

    COORD_INT(TASK(Actor)->pos.z) = -128;
    TASK(Actor)->screen_y         = 0;
    TASK(Actor)->header.step++;
    work = TASK(Actor);
    if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(work->pos.y) + 1) | COORD_HALF)) > COORD_HALF) {
        goto call;
    }
    if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x))) > TO_COORD(1) && abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x) + 1)) > TO_COORD(1)) {
        goto call;
    }
    work->screen_y    = 192;
    work->header.step = 3;
call:
    Area_Update();
}
