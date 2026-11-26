#include "engine/game/00/game_00.h"

/* func_8019AF1C */
/* Loads the rise speed and gravity of its toss arc when on the ground, then moves by its speeds under gravity. */
MATCH void Actor_TossLaunch(void) {
    Actor* work;
    s16    dist;

    dist = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    work = TASK(Actor);
    if (dist >= COORD_INT(work->pos.z) || (work->header.flags & ACTOR_FLAG_OFFSCREEN) || work->header.mode == 0) {
        work->vz      = s_ActorTossArcs[work->header.step].vz;
        work->gravity = s_ActorTossArcs[work->header.step].gravity;
        work->header.mode++;
    }
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    TASK(Actor)->vz -= TASK(Actor)->gravity;
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
