#include "game_00.h"

MATCH void func_8019AAFC(void) {
    Actor* work;
    u8*    flags;

    work  = TASK(Actor);
    flags = &g_ScenarioState.flags_01;
    setVector(&g_AreaCameraAngle, work->unk_64, work->unk_68, work->unk_6C);
    *flags &= ~SCENARIO_STATE_CAMERA_MOVING;
    Actor_Clear();
}
