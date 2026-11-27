#include "engine/game/00/game_00.h"

/* func_8019ACF4 */
/* Steps the angle pan and moves the camera z offset toward the target, stopping at it. */
MATCH void Camera_PanZoomStep(void) {
    Actor* work;
    s32    pos;
    s32    step;

    Camera_PanAngleStep();
    work                = SELF(Actor);
    pos                 = (g_AreaCameraOffsetZ << 16) + work->vy;
    /* FAKE: volatile re-read keeps the direction load before the store.
     */
    step                = FIELD(volatile s32, work, 0x10u);
    g_AreaCameraOffsetZ = (pos >> 16);
    if (step < 0) {
        if (g_AreaCameraOffsetZ < work->vx) {
            g_AreaCameraOffsetZ = work->vx;
        }
    } else {
        if (g_AreaCameraOffsetZ > work->vx) {
            g_AreaCameraOffsetZ = work->vx;
        }
    }
}
