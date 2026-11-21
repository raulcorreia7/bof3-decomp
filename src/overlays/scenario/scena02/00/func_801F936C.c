#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "shared/etc.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F936C(void) {
    switch (g_ScenarioState.step_05) {
        case 0: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] == 0x64) {
                vars[0] = 0;
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step_05 = 0x14;
            }
            if (vars[0] == 0x65) {
                vars[0]         = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        }
        case 0x14:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step_05 = 0x15;
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            break;
        case 0x15:
            SND_StartXAStream(0, 1);
            g_ScenarioState.step_05 = 0x16;
            break;
        case 0x16:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            g_ScenarioState.step_05 = 0x17;
            break;
        case 0x17:
            if (g_Game.party_size == 3) {
                g_ScriptVars[2]         = 5;
                g_ScenarioState.step_05 = 0x18;
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x51), TO_COORD(8), 0x85);
            } else {
                g_ScriptVars[2]         = 5;
                g_ScenarioState.step_05 = 0x18;
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE, TO_COORD(0x50), TO_COORD(5), 0x86);
            }
            SND_PlayBGM(7, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            break;
        case 0x18:
            if (g_ScriptVars[0] == 1) {
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 0xC8) {
                D_8014865C              = -2;
                D_80148698              = 1;
                g_GameEntryState        = GAME_MODE_SHOP;
                g_MenuStep.step         = 0;
                D_80148699              = 0;
                g_ScenarioState.step_05 = 3;
            } else if (g_ScriptVars[0] == 0xC9) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 7:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 0xC8) {
                D_8014865C              = -2;
                D_80148698              = 1;
                g_GameEntryState        = GAME_MODE_SHOP;
                g_MenuStep.step         = 0;
                D_80148699              = 0;
                g_ScenarioState.step_05 = 3;
            } else if (g_ScriptVars[0] == 0xC9) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 3:
            if (g_GameStateIndex == 0) {
                SCRIPT_VARS_CLEAR_ALL();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 8:
            if (g_GameStateIndex == 0) {
                SCRIPT_VARS_CLEAR_ALL();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
