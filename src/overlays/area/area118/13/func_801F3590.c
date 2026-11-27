#include "area118_13.h"

MATCH void func_801F3590(void) {
    Actor* work;

    if (g_GameCellType == 0 && g_AreaSceneMode == SELF(Actor)->unk_0A) {
        return;
    }
    work = SELF(Actor);
    /* FAKE: keeps the work pseudo first in allocation, so the task pointer stays in a1 as retail has it. */
    FAKE_USE(work);
    if (work->direction != 0) {
        if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(work->pos.y) + 1) | COORD_HALF)) > TO_COORD(2)) {
            goto advance;
        }
        if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x))) <= TO_COORD(2)) {
            return;
        }
        if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(work->pos.x) + 1)) <= TO_COORD(2)) {
            return;
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(work->pos.x) + 1) | COORD_HALF)) > TO_COORD(2)) {
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
    work->header.step = 4;
}
