#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FC280(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_SceneState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801FC280);
#endif
