#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F87C4(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            break;
        case 1:
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_013, 3);
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]         = 0x1E;
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            g_ScenarioState.step_05 = 5;
            Scene_SetupParty(6);
            break;
        case 5:
            if (g_ScriptVars[0] == 0x23) {
                g_ScriptVars[2]         = 4;
                g_ScriptVars[1]         = 1;
                g_ScenarioState.step_05 = 6;
                Game_RequestAreaChange(AREA_ID_DUMP, TO_COORD(133), TO_COORD(16), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                g_GamePrevSelection = 0x3B;
            }
            break;
        case 6:
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 5;
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;
        case 19:
            break;
        case 20:
            break;
        case 21:
            break;
        case 22:
            break;
        case 23:
            break;
        case 24:
            break;
        case 25:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_013, 0x1A);
            break;
        case 26:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0x28;
                Area_StartScrollRoute(1);
                g_ScenarioState.step_05 = 0x1B;
            }
            break;
        case 27:
            Scene_SetupParty(8);
            g_ScenarioState.step_05 = 0x1C;
            break;
        case 28: {
            u8* progress = &g_ScriptVars[0];

            if (*progress == 0x2C) {
                g_ScenarioState.step_05 = 0x1D;
                *progress               = 0x2D;
                SND_StopSequence(0, 2);
            }
            break;
        }
        case 29:
            if (g_ScriptVars[0] == 0x32) {
                SND_PlayBGM(0x39, 0x64, 8);
                g_ScenarioState.step_05 = 0x1F;
            }
            break;
        case 30:
            break;
        case 31:
            if (g_ScriptVars[0] == 0x50) {
                SND_StopSequence(0, 1);
                UI_ModeSet(0xD);
                g_ScenarioState.step_05 = 0x20;
            }
            break;
        case 32:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_PlaySequence(0, 3, 0x64, 0x64);
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_019, 0x21);
            break;
        case 33:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 8);
                Scene_RunScenario(0);
                g_ScenarioState.step_05 = 0x22;
                g_ScriptVars[0]         = 0x51;
            }
            break;
        case 34:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                g_ScriptVars[2]         = 5;
                g_ScenarioState.step_05 = 0x23;
                Game_RequestAreaChange(AREA_ID_DUMP, TO_COORD(133), TO_COORD(21), 0x89);
                g_GamePrevSelection = 0x38;
            }
            break;
        case 35:
            SYS_SetFlag(g_SceneFlags, 9);
            g_GameFlags ^= 0x20;
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            SCENARIO_RETURN_TO_START();
            break;
    }
}
