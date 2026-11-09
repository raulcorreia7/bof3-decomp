#include "area171_13.h"

MATCH void func_801F2F5C(void) {
    Actor* work;

    work = g_Task;
    if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(work->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2)) {
        goto advance;
    }
    if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(work->pos.y) << 16)) <= TO_COORD(2)) {
        return;
    }
    if (abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(work->pos.y) + 1) << 16)) <= TO_COORD(2)) {
        return;
    }
advance:
    work->header.step++;
}
