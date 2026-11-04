#include "area095_13.h"

MATCH void func_801F2D3C(void) {
    if ((SYS_TestFlag(g_SceneEventFlags, 0x22) != 0) ||
        ((SYS_TestFlag(g_SceneEventFlags, 0x21) != 0) && (g_SceneState.scenario_id < 8))) {
        g_AreaSceneMode               = 1;
        ((Actor*)g_SpadWork)->z.fixed = -0x100;
        ((Actor*)g_SpadWork)->unk_0B  = 0x80;
        ((Actor*)g_SpadWork)->unk_09  = 0xA;
        ((Actor*)g_SpadWork)->state_02 += 1;
        func_801F2F3C(-0x100, 0x80);
    }
}
