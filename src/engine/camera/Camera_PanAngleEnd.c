#include "engine/game/00/game_00.h"

/* func_8019AAFC */
/* Sets the camera angle to the actor's angle, clears the camera-moving flag and frees the actor. */
MATCH void Camera_PanAngleEnd(void) {
    Actor* work;
    u8*    flags;

    work  = TASK(Actor);
    flags = &g_ScenarioState.flags_01;
    setVector(&g_AreaCameraAngle, work->angle_x, work->angle_y, work->angle_z);
    *flags &= ~SCENARIO_STATE_CAMERA_MOVING;
    Actor_Clear();
}
