#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FCD80(void) {
    switch (g_ScenarioState.step_05) {
        case 1:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x38);
            g_GamePrevSelection     = 0x7B;
            g_ScenarioState.step_05 = 1;
            break;
        case 2:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x39);
            g_GameFlags |= 0x10;
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x3A);
            g_GameFlags &= ~0x10;
            g_ScriptVars[0] = 0;
            break;
        case 4:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_SetScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x3B);
            g_GameFlags &= ~0x10;
            func_801C1E3C(3);
            break;
        case 5:
            Message_StartAreaMessage(0x3A);
            g_GameStateIndex        = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step_05 = 0xB;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801FCD80);
#endif
