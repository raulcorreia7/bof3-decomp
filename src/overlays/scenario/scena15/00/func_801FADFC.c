#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FADFC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_InputHeld != 0) {
                g_ScriptVars[0]      = 2;
                g_SceneState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 3) {
                g_SpawnedActors[D_801FE748].header.mode = 2;
                g_SceneState.step_05                    = 2;
            }
            break;
        case 2:
            break;
        case 3:
            func_801C7A54(D_801FE608[g_SpawnedActors[D_801FE748].link * 10 + 9]);
            g_SceneState.timer_06 = 0x78;
            g_SceneState.step_05  = 4;
            break;
        case 4:
            break;
        case 5:
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, D_801FE608[g_SpawnedActors[D_801FE748].link * 10 + 8]);
            g_ScriptVars[0]       = 0;
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
            break;
    }
}
