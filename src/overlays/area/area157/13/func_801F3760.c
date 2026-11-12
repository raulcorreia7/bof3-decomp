#include "area157_13.h"

MATCH void func_801F3760(void) {
    Actor* work;

    work = g_Task;
    if (work->direction_08 != 0) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(work->pos.y) - 2) << 16) | 0x8000)) > COORD_HALF) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x))) <= TO_COORD(2)) {
            return;
        }
        if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x) + 1)) <= TO_COORD(2)) {
            return;
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(work->pos.x) - 2) << 16) | 0x8000)) > COORD_HALF) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(work->pos.y))) <= TO_COORD(2)) {
            return;
        }
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(work->pos.y) + 1)) <= TO_COORD(2)) {
            return;
        }
    }
advance:
    work->header.step++;
}
