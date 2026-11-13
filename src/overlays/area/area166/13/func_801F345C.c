#include "area166_13.h"

MATCH void func_801F345C(void) {
    Actor* scratch;
    Actor* work;
    s32    index;
    s16    screen_y;

    scratch                = g_Task;
    index                  = COORD_INT(scratch->pos.x);
    scratch->direction_08  = (COORD_INT(scratch->pos.y) == 0);
    work                   = g_Task;
    COORD_INT(work->pos.x) = D_801F3748[index][0];
    COORD_INT(work->pos.y) = D_801F3748[index][1];
    COORD_INT(work->pos.z) = -128;

    if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(work->pos.y) + 1) | COORD_HALF)) > COORD_HALF) {
        goto reset;
    }
    if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x))) > TO_COORD(1) && abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x) + 1)) > TO_COORD(1)) {
        goto reset;
    }
    screen_y       = -256;
    work->screen_y = screen_y;
    work->header.step++;
    return;

reset:
    g_Task->screen_y    = 0;
    g_Task->header.step = 3;
}
