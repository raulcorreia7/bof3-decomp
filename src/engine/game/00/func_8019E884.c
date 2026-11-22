#include "game_00.h"

MATCH void func_8019E884(void) {
    Actor* work;
    s32    add;
    s16    dist;

    add             = TASK(Actor)->vz + TASK(Actor)->gravity;
    TASK(Actor)->vz = add;
    COORD_INT(TASK(Actor)->pos.z) += add;
    Script_AnimStepLoop();
    work = TASK(Actor);
    dist = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    if (COORD_INT(work->pos.z) < dist) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
