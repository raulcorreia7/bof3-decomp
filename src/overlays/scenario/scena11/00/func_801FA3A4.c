#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA3A4(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                func_801BE1B0(9);
                g_SceneState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 7) {
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                func_801BE1B0(10);
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 6) {
                g_SceneState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0xF) {
                UI_SetMode(4);
                g_SceneState.step_05 = 8;
            }
            break;
        case 8:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                Message_StartAreaMessage(0x3F);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 9;
            }
            break;
        case 9:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                Scene_RequestChapterAdvance();
                g_ScriptVars[2] = 2;
                g_GameFlags ^= 0x16;
                Game_RequestAreaChange(0x79, 0x290000, 0x330000, 7);
            }
            break;
    }
}
