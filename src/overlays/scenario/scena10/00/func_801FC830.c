#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC830(void) {
    if (g_ScenarioState.step == 1) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
            Scene_SetupParty(2);
            SYS_SetFlag(g_SceneFlags, 52);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
        }
    }
}

MATCH void func_801FC8A0(void) {
    if (g_ScenarioState.step == 0x23) {
        Game_ClearScriptActive();
        Scene_SetupParty(4);
        *g_ScriptVars            = 0x20;
        g_ScenarioState.state_04 = 0;
        g_ScenarioState.step     = 0;
    }
}
