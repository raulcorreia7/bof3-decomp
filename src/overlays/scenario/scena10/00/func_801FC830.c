#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC830(void) {
    if (g_SceneState.step_05 == 1) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
            func_801BE1B0(2);
            SYS_SetFlag(g_SceneFlags, 52);
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
        }
    }
}

MATCH void func_801FC8A0(void) {
    if (g_SceneState.step_05 == 0x23) {
        Game_ClearScriptActive();
        func_801BE1B0(4);
        *g_ScriptVars         = 0x20;
        g_SceneState.state_04 = 0;
        g_SceneState.step_05  = 0;
    }
}
