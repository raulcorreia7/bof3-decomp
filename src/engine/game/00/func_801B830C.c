#include "game_00.h"

MATCH void func_801B830C(void) {
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
