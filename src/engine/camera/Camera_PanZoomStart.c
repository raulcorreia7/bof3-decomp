#include "engine/game/00/game_00.h"

/* func_8019AC84 */
/* Starts the angle pan and sets the per-frame step of the camera z offset toward the actor's target. */
MATCH void Camera_PanZoomStart(void) {
    Actor* work;

    Camera_PanAngleStart();
    work     = TASK(Actor);
    work->vy = ((work->vx - g_AreaCameraOffsetZ) << 0x10) / work->timer;
}
