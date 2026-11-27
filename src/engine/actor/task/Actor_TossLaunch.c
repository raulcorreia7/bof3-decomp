#include "engine/game/00/game_00.h"

/* func_8019AF1C */
/* Loads the rise speed and gravity of its toss arc when on the ground, then moves by its speeds under gravity. */
MATCH void Actor_TossLaunch(void) {
    Actor* work;
    s16    dist;

    dist = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    work = SELF(Actor);
    if (dist >= COORD_INT(work->pos.z) || (work->header.flags & ACTOR_FLAG_OFFSCREEN) || work->header.mode == 0) {
        work->vz      = s_ActorTossArcs[work->header.step].vz;
        work->gravity = s_ActorTossArcs[work->header.step].gravity;
        work->header.mode++;
    }
    SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
    SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
    SELF(Actor)->pos.z.fixed += SELF(Actor)->vz;
    SELF(Actor)->vz -= SELF(Actor)->gravity;
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
