#include "area151_13.h"

/* Moves the actor along its flight path. */
/* func_801F4494 */
MATCH void Actor_Fly(void) {
    Actor* scratch;
    Actor* work;

    scratch = TASK(Actor);
    if (scratch->param.unk_0B != 0) {
        if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch->param.unk_0B = 1;
    }

    work = TASK(Actor);
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    Script_AnimStepLoop();
    Area_AddGridActor();
}
