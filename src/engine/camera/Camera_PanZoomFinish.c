#include "engine/game/00/game_00.h"

/* func_8019AD70 */
/* Sets the camera z offset to the target and finishes the angle pan. */
MATCH void Camera_PanZoomFinish(void) {
    Actor* work;

    work                = TASK(Actor);
    g_AreaCameraOffsetZ = work->vx;
    Camera_PanAngleFinish();
}
