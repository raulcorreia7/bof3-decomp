#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA8EC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            if (!SYS_TestFlag(g_SceneFlags, 39)) {
                Message_StartAreaMessage(8);
            } else {
                Message_StartAreaMessage(0xA);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            if (SYS_TestFlag(g_SceneFlags, 39)) {
                Message_StartAreaMessage(0xA);
            } else if (SYS_TestFlag(g_SceneFlags, 37)) {
                Message_StartAreaMessage(8);
            } else {
                Message_StartAreaMessage(9);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 6;
                break;
            }
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 1) {
                    g_SceneState.step_05 = 7;
                    break;
                }
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 7:
            func_801BE1B0(0);
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_SceneState.step_05 = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 37);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
