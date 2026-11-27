#include "engine/game/00/game_00.h"

/* func_8019AA44 */
/* Adds the step to the camera angle for each of the timer frames, then moves to the end mode. */
MATCH void Camera_PanAngleStep(void) {
    Actor*  work;
    Angle3* angle;

    work = SELF(Actor);
    if (work->timer != 0) {
        angle = &D_801481E8;
        angle->x += D_801481F8.x;
        angle->y += D_801481F8.y;
        angle->z += D_801481F8.z;
        setVector(&g_AreaCameraAngle, (angle->x >> 16), (angle->y >> 16), (angle->z >> 16));
        work->timer--;
        return;
    }
    work->header.mode = 2;
}
