#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA8EC(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScenarioState.step = 1;
            if (!SYS_TestFlag(g_SceneFlags, 39)) {
                UI_MessageStartArea(MSG_SCENA06_008);
            } else {
                UI_MessageStartArea(MSG_SCENA06_010);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            if (SYS_TestFlag(g_SceneFlags, 39)) {
                UI_MessageStartArea(MSG_SCENA06_010);
            } else if (SYS_TestFlag(g_SceneFlags, 37)) {
                UI_MessageStartArea(MSG_SCENA06_008);
            } else {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA06_009, 6);
                break;
            }
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 1) {
                    g_ScenarioState.step = 7;
                    break;
                }
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 7:
            Scene_SetupParty(0);
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 37);
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
    }
}
