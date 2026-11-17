#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9354(void) {
    u8* step = &g_SceneState.step_05;
    u8* vars;

    switch (*step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                *g_ScriptVars = 1;
                Scene_SetupParty(0xC);
                *step = 1;
            }
            break;
        case 1:
            if (*g_ScriptVars == 9) {
                SYS_SetFlag(g_SceneFlags, 0x3F);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                *step                 = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                *g_ScriptVars = 1;
                *step         = 6;
            }
            break;
        case 6:
            vars = g_ScriptVars;
            if (*vars == 2) {
                Game_ClearScriptActive();
                *vars                 = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                *step                 = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
