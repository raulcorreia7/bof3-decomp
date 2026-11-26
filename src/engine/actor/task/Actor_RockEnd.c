#include "engine/game/00/game_00.h"

/* func_8019BE28 */
/* Scales the rock up each frame and removes it once it has doubled and the camera is still. */
MATCH void Actor_RockEnd(void) {
    Actor* work;

    TASK(Actor)->unk_48 = 2;
    work                = TASK(Actor);
    work->scale.x += 0x4000;
    work->scale.y += 0x4000;
    if (work->timer != 0) {
        if (g_AreaCameraMoving == 0) {
            work->timer = (work->timer - 1);
        }
    }
    if (TASK(Actor)->scale.x > 131071) {
        if ((g_AreaCameraMoving == 0) && (TASK(Actor)->timer == 0)) {
            Actor_RockReleaseCamera();
            Actor_Clear();
        }
    } else {
        Area_SetDrawMode();
    }
}
