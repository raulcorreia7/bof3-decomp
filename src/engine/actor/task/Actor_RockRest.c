#include "engine/game/00/game_00.h"

/* func_8019BEFC */
/* Counts the rest timer down and returns the camera and the rock to waiting. */
MATCH void Actor_RockRest(void) {
    Actor* work;
    u8     count;
    work  = SELF(Actor);
    count = work->timer;
    if (count != 0) {
        work->timer = (count - 1);
    }
    if (g_AreaCameraMoving == 0) {
        work = SELF(Actor);
        if (work->timer == 0) {
            work->header.mode = ACTOR_ROCK_MODE_WAIT;
            Actor_RockReleaseCamera();
        }
    }
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
