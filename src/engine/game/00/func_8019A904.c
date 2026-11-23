#include "game_00.h"

MATCH void func_8019A904(void) {
    Actor* work;
    s32    pos_x;
    s32    pos_y;
    s32    pos_z;

    work                     = TASK(Actor);
    pos_x                    = g_AreaCameraAngle.vx;
    pos_y                    = g_AreaCameraAngle.vy;
    pos_z                    = g_AreaCameraAngle.vz;
    D_801481E8.x             = pos_x << 0x10;
    D_801481E8.y             = pos_y << 0x10;
    D_801481E8.z             = pos_z << 0x10;
    D_801481F8.x             = ((work->angle_x - pos_x) << 0x10) / work->timer;
    D_801481F8.y             = ((work->angle_y - pos_y) << 0x10) / work->timer;
    D_801481F8.z             = ((work->angle_z - pos_z) << 0x10) / work->timer;
    g_AreaCameraRefreshCount = work->timer;
    g_ScenarioState.flags_01 |= SCENARIO_STATE_CAMERA_MOVING;
    work->header.mode = 1;
}
