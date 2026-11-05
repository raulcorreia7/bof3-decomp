#include "game_00.h"

MATCH void func_8019AAFC(void) {
    Actor* work;
    u8*    flags;

    work                 = g_Task;
    flags                = &g_SceneState.flags_01;
    g_AreaCameraAngle.vx = (s16)work->unk_64;
    g_AreaCameraAngle.vy = (s16)work->unk_68;
    g_AreaCameraAngle.vz = (s16)work->unk_6C;
    *flags &= ~SCENE_STATE_CAMERA_MOVING;
    Actor_Clear();
}
