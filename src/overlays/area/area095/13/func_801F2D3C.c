#include "area095_13.h"

MATCH void func_801F2D3C(void) {
    if ((SYS_TestFlag(g_SceneEventFlags, 34) != 0) || ((SYS_TestFlag(g_SceneEventFlags, 33) != 0) && (g_SceneState.scenario_id < 8))) {
        g_AreaSceneMode      = 1;
        g_Task->pos.z.fixed  = -0x100;
        g_Task->param.unk_0B = 0x80;
        g_Task->timer        = 10;
        g_Task->header.step += 1;
        func_801F2F3C(-0x100, 0x80);
    }
}
