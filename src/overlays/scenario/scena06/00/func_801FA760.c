#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA760(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                func_801BE1B0(7);
                g_SceneState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0x08) {
                SND_PauseBGM(0x42);
                SND_StartXAStream(2, 1);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (SND_IsXAIdle() != 0) {
                SND_ResumeBGM(0x42);
                g_ScriptVars[0]      = 9;
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x0A) {
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            func_801BE1B0(8);
            SYS_SetFlag(g_SceneFlags, 0x24);
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x17) {
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
    }
}
