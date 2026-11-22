#include "scena01_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC488(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScenarioState.step = 3;
            SND_SeqStop(0, 0);
            SND_BGMPlay(0x11, 0x64, 8);
            g_AreaDrawFlags = 0;
            g_GameFlags |= 0x80;
            MESSAGE_START_WAIT(MSG_SCENA01_016);
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]      = 1;
                g_ScenarioState.step = 4;
                SYS_SetFlag(g_SceneFlags, 0x3E);
                Game_RequestAreaChange(AREA_ID_FARM, TO_COORD(8), TO_COORD(83), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 7) {
                UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (WINDOW_EFFECT_IDLE()) {
                D_80146871 |= 1;
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 7;
                Area_InitMapRenderer();
                g_ScriptVars[0] = 8;
                MESSAGE_START_WAIT(MSG_SCENA01_028);
            }
            break;
        case 7:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_ModeSet(UI_MODE_LONG_FADE_IN);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVars[0]      = 9;
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 0x14) {
                SCENARIO_RETURN_TO_START();
                g_AreaDrawFlags = 0;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_AREA, TO_COORD(54), TO_COORD(80), 0);
                Scene_RequestChapterAdvance();
            }
            break;
    }
}
