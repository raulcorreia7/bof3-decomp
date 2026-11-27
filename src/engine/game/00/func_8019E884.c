#include "game_00.h"

MATCH void func_8019E884(void) {
    Actor* work;
    s32    add;
    s16    dist;

    add             = SELF(Actor)->vz + SELF(Actor)->gravity;
    SELF(Actor)->vz = add;
    COORD_INT(SELF(Actor)->pos.z) += add;
    Script_AnimStepLoop();
    work = SELF(Actor);
    dist = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    if (COORD_INT(work->pos.z) < dist) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
