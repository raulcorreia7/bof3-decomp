#include "engine/game/00/game_00.h"

/* func_8019B024 */
/* Moves the actor up by its vertical speed under gravity until it is 0x80 above the ground or below it, with a sound. */
MATCH void Actor_TossFall(void) {
    Actor* work;
    s16    dist;
    s16    counter;
    s32    diff;

    dist    = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    counter = COORD_INT(TASK(Actor)->pos.z);
    if ((counter >= dist + 0x80) || (counter < dist) || (TASK(Actor)->header.flags & ACTOR_FLAG_OFFSCREEN)) {
        work = TASK(Actor);
        work->header.mode++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    }
    TASK(Actor)->pos.z.fixed += TASK(Actor)->vz;
    diff            = TASK(Actor)->vz - TASK(Actor)->gravity;
    TASK(Actor)->vz = diff;
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
