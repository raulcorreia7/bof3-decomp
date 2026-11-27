#include "area095_13.h"

MATCH void func_801F2D3C(void) {
    if ((SYS_TestFlag(g_SceneEventFlags, 34) != 0) || ((SYS_TestFlag(g_SceneEventFlags, 33) != 0) && (g_ScenarioState.scenario_id < 8))) {
        g_AreaSceneMode           = 1;
        SELF(Actor)->pos.z.fixed  = -0x100;
        SELF(Actor)->param.unk_0B = 0x80;
        SELF(Actor)->timer        = 10;
        SELF(Actor)->header.step += 1;
        func_801F2F3C(-0x100, 0x80);
    }
}
