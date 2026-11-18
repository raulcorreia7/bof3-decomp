#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7C38(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScenarioState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_AREA, TO_COORD(0x36), TO_COORD(0x50), AREA_ENTRY_MAP_LOADING);
            break;
        case 1:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 8) {
                D_80146258 |= 6;
                Game_ClearScriptActive();
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                SCENARIO_RETURN_TO_START();
                SYS_SetFlag(g_SceneFlags, 4);
            }
            break;
        case 5:
            Scene_SetupParty(1);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                SCENARIO_RETURN_TO_START();
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                D_80146258 ^= 0xB0;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(0x31), TO_COORD(0x4B), 0x85);
            }
            break;
        case 7:
            Scene_SetupParty(2);
            g_ScenarioState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                D_80146258 ^= 0xB0;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(0x31), TO_COORD(0x4B), 0x85);
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x1E) {
                g_ScriptVars[2] = 0;
                SCENARIO_RETURN_TO_START();
                if (g_Game.party_size == 3) {
                    D_80146258 ^= 0x80;
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(0x31), TO_COORD(0x4B), 0x85);
                } else {
                    D_80146258 ^= 0x80;
                    Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(0x31), TO_COORD(0x4B), 0x8B);
                }
            }
            break;
        case 30: {
            u8* vars;

            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            vars = g_ScriptVars;
            if (vars[0] == 0x64) {
                vars[0]                 = 0;
                g_ScenarioState.step_05 = 0x1F;
                UI_SetMode(0xD);
                Char_RebuildPartyStats();
                SND_FadeOutSequence(0, 1, 4, 0x1E);
            } else if (vars[0] == 0x65) {
                Game_ClearScriptActive();
                vars[0] = 0;
                SCENARIO_RETURN_TO_START();
            }
            break;
        }
        case 31:
            SND_StartXAStream(0, 1);
            g_ScenarioState.step_05 = 0x20;
            break;
        case 32:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            if (SND_IsXAIdle() != 0) {
                g_ScenarioState.step_05 = 0x21;
            }
            break;
        case 33:
            UI_SetMode(0xE);
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 0x22;
            break;
        case 34:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_PlayBGM(0x11, 0x64, 8);
            SCENARIO_MESSAGE_WAIT(MSG_SCENA02_010, 0x23);
            break;
        case 35:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
