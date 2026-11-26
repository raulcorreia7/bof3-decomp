#include "engine/game/00/game_00.h"

/* func_801B830C */
/* Walks the actor out and requests the area change on the third step. */
MATCH void Party_WalkExit(void) {
    u8 step;

    if (TASK(Actor)->timer == 0) {
        step                = TASK(Actor)->unk_0A + 1;
        TASK(Actor)->unk_0A = step;
        if (step == 3) {
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
        }
        Area_RunWalk();
    }
    TASK(Actor)->timer = TASK(Actor)->timer - 1;
    Actor_MovementUpdate();
    Script_AnimStepLoop();
}
