#include "scena01_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC6B4(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0x64) {
                    g_ScriptVars[0]         = 0;
                    g_ScenarioState.step_05 = 1;
                    UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                    func_801C16B8();
                    SND_SeqFadeOut(0, 0, 4, 0x1E);
                } else if (g_ScriptVars[0] == 0x65) {
                    Game_ClearScriptActive();
                    g_ScriptVars[0] = 0;
                    g_ScriptVars[1] = 0;
                    g_ScriptVars[2] = 0;
                    SCENARIO_RETURN_TO_START();
                }
            }
            break;
        case 1:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                if (SND_XAIsIdle() & BYTE_MASK) {
                    g_ScenarioState.step_05 = 3;
                }
            }
            break;
        case 3:
            UI_ModeSet(UI_MODE_LONG_FADE_IN);
            g_AreaDrawFlags         = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            if (!WINDOW_EFFECT_BUSY()) {
                SND_BGMPlay(27, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                SCENARIO_MESSAGE_WAIT(MSG_SCENA01_010, 5);
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
