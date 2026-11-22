#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F8DFC(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x21);
            g_ScenarioState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801F8DFC);
#endif
