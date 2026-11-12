#include "area140_13.h"

MATCH void func_801F2C78(void) {
    Actor* work;
    s16    screen_y;

    COORD_INT(g_Task->pos.z) = -1472;
    g_Task->screen_y         = 0;
    g_Task->header.step++;
    if (!SYS_TestFlag(g_SceneEventFlags, 84)) {
        g_Task->header.step = 5;
    } else {
        work = g_Task;
        if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(work->pos.x) + 1) | COORD_HALF)) > COORD_HALF) {
            goto call;
        }
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(work->pos.y))) > TO_COORD(1) && abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(work->pos.y) + 1)) > TO_COORD(1)) {
            goto call;
        }
        screen_y          = -256;
        work->screen_y    = screen_y;
        work->header.step = 3;
    }
call:
    func_801F3050();
}
