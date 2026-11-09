#include "area173_14.h"

MATCH void func_801F44B4(void) {
    Actor* work;

    work = g_Task;
    if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(work->pos.y) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
        goto advance;
    }
    if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(work->pos.x) << 16)) <= TO_COORD(2)) {
        goto call;
    }
    if (abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(work->pos.x) + 1) << 16)) <= TO_COORD(2)) {
        goto call;
    }
advance:
    work->header.step++;
call:
    Area_Update();
}
