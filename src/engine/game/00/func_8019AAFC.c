#include "game_00.h"

MATCH void func_8019AAFC(void) {
    Actor* work;
    u8*    flags;

    work  = TASK(Actor);
    flags = &g_ScenarioState.flags_01;
    setVector(&g_AreaCameraAngle, work->angle_x, work->angle_y, work->angle_z);
    *flags &= ~SCENARIO_STATE_CAMERA_MOVING;
    Actor_Clear();
}
