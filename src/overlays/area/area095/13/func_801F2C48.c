#include "area095_13.h"

MATCH void func_801F2C48(void) {
    u8* width;

    if ((SYS_TestFlag(g_SceneEventFlags, 34) != 0) || ((SYS_TestFlag(g_SceneEventFlags, 33) != 0) && (g_SceneState.scenario_id < 8))) {
        g_AreaSceneMode = 1;
        func_80196070();
    } else {
        width                               = MEM_PTR(u8, 0x80104000u);
        g_AreaCellCodes[*width * 60 + 0x45] = 0x10;
        g_AreaCellCodes[*width * 60 + 0x46] = 0x10;
        func_801F2F3C(-0x100, 0x80);
        g_Task->header.step += 1;
    }
}
