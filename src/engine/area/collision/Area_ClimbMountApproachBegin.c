#include "engine/game/00/game_00.h"

/* func_801C4D58 */
/* Starts the mount approach: sets the walk velocity and the move timer, requests the animation of the facing plus 8 and moves one frame. */
MATCH void Area_ClimbMountApproachBegin(void) {
    Actor* work;
    Actor* state;
    Actor* reload;
    s32    doubled;

    g_Game.current->u.field.counter.value = (TASK(Actor)->voice_flags.raw + 2);
    Area_SetWalkVelocity();
    work          = TASK(Actor);
    doubled       = work->timer * 2;
    work->timer   = (doubled * (work->voice_flags.raw + 1));
    state         = TASK(Actor);
    work->vz      = 0;
    state->unk_0A = (state->timer >> 1);
    Script_Request((TASK(Actor)->direction + 8) & BYTE_MASK);
    Actor_Move();
    reload        = TASK(Actor);
    reload->timer = (reload->timer - 1);
}
