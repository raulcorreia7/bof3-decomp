#include "scena05_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F96E0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (!(g_UiWindowChannel & FRONTEND_FLAG_CONFIRM)) {
                break;
            }
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Message_StartAreaMessage(35);
                    break;
                case 2:
                    Message_StartAreaMessage(36);
                    break;
                default:
                    return;
            }
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 2) {
                if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                    g_SceneState.step_05 = 2;
                }
                break;
            }
            if (g_ScriptVars[0] == 0x0A) {
                g_SceneState.step_05 = 4;
            }
            break;
        case 2:
            SCENE_MESSAGE_WAIT(37, 3);
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                D_80146865            = 0;
                D_80146866            = 0;
                D_80146867            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x14) {
                SYS_SetFlag(g_SceneFlags, 0x1A);
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                D_80146865            = 0;
                D_80146866            = 0;
                D_80146867            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
