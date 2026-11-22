#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA760(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(7);
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0x08) {
                SND_BGMPause(0x42);
                SND_XAStartStream(2, 1);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (SND_XAIsIdle() != 0) {
                SND_BGMResume(0x42);
                g_ScriptVars[0]         = 9;
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x0A) {
                Game_ClearScriptActive();
                g_ScenarioState.step_05  = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            Scene_SetupParty(8);
            SYS_SetFlag(g_SceneFlags, 0x24);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x17) {
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
    }
}
