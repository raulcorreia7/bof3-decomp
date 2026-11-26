#include "engine/game/00/game_00.h"

/* func_8019A904 */
/* Sets the per-frame step from the camera angle to the actor's angle over its timer frames, then starts the step mode. */
MATCH void Camera_PanAngleStart(void) {
    Actor* work;
    s32    start_x;
    s32    start_y;
    s32    start_z;

    work                     = TASK(Actor);
    start_x                  = g_AreaCameraAngle.vx;
    start_y                  = g_AreaCameraAngle.vy;
    start_z                  = g_AreaCameraAngle.vz;
    D_801481E8.x             = start_x << 0x10;
    D_801481E8.y             = start_y << 0x10;
    D_801481E8.z             = start_z << 0x10;
    D_801481F8.x             = ((work->angle_x - start_x) << 0x10) / work->timer;
    D_801481F8.y             = ((work->angle_y - start_y) << 0x10) / work->timer;
    D_801481F8.z             = ((work->angle_z - start_z) << 0x10) / work->timer;
    g_AreaCameraRefreshCount = work->timer;
    g_ScenarioState.flags_01 |= SCENARIO_STATE_CAMERA_MOVING;
    work->header.mode = 1;
}
