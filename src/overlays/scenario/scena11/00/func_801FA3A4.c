#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA3A4(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(9);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 7) {
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(10);
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 6) {
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0xF) {
                UI_ModeSet(4);
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (g_UIWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA11_063, 9);
            }
            break;
        case 9:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
                Scene_RequestChapterAdvance();
                g_ScriptVars[2] = 2;
                g_GameFlags ^= 0x16;
                Game_RequestAreaChange(0x79, 0x290000, 0x330000, 7);
            }
            break;
    }
}
