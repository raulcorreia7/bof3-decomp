#include "engine/game/00/game_00.h"

/* func_801B7FE0 */
/* Lowers the actor down the ladder to the ground. */
MATCH void Party_LadderDownDescend(void) {
    Actor* work;
    Actor* store;
    s16    value;
    u8     arg;

    work = TASK(Actor);
    COORD_INT(work->pos.z) -= 16;
    if ((s16)COORD_INT(work->pos.z) < Area_HeightRead(work->pos.x.fixed, work->pos.y.fixed)) {
        value                   = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
        store                   = TASK(Actor);
        store->timer            = 2;
        COORD_INT(store->pos.z) = value;
        TASK(Actor)->unk_0A     = 0;
        Script_Request((TASK(Actor)->direction == FACING_RIGHT) ? 7 : 1);
        TASK(Actor)->unk_04 = 9;
    }
    Script_AnimStepLoop();
}
