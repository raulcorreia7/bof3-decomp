#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA08C(void) {
    u8* step = &g_ScenarioState.step;

    switch (*step) {
        case 0:
            if (D_8014623B != 2) {
                Scene_SetupParty(0);
                *step = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            if (!(g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_MENU]) && g_GameStateIndex == GAME_REQUEST_IDLE) {
                *g_ScriptVars = 0;
                *step         = 6;
                Game_RequestAreaChange(0x76, 0x490000, 0x188000, 0x81);
            }
            break;
        case 6:
            if (*g_ScriptVars == 1 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                *g_ScriptVars = 0;
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
