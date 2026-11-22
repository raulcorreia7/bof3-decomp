#include "scena06_00.h"
#include "area/map.h"
#include "menu/gameui.h"
#include "menu/message_ids.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Runs the scene script one step per frame, keyed on g_ScenarioState.step_05. */
MATCH void func_801F97C0(void) {
    u8* state;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]         = 1;
                g_ScenarioState.step_05 = 2;
                g_ScenarioState.flags_01 |= 1;
                Game_RequestAreaChange(0x5C, TO_COORD(14), TO_COORD(60), 0x80);
                g_GamePrevSelection = 0xFF;
            }
            break;
        case 2:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_001, 3);
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                func_801C601C(0);
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 2) {
                g_GameStateIndex        = 7;
                D_8018E244              = 0;
                g_AreaDrawFlags         = 0;
                g_ScenarioState.step_05 = 5;
            }
            break;
        case 5:
            if (g_GameStateIndex == 0) {
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 6:
            if (D_80144DF2 == 0) {
                g_ScenarioState.step_05 = 0xE;
            } else if (D_80144DF5 != 0) {
                g_ScenarioState.step_05 = 0xA;
            } else {
                g_ScenarioState.step_05 = 0xE;
            }
            break;
        case 10:
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 0xB;
            SYS_SetFlag(g_SceneFlags, 0x1A);
            SYS_SetFlag(g_SceneFlags, 0x1B);
            Game_RequestAreaChange(0x5C, TO_COORD(25), TO_COORD(60), 0x81);
            g_GamePrevSelection = 0x3C;
            break;
        case 14:
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 0xF;
            SYS_SetFlag(g_SceneFlags, 0x17);
            Game_RequestAreaChange(0x5C, TO_COORD(25), TO_COORD(60), 0x82);
            break;
        case 18:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                SYS_SetFlag(g_SceneFlags, 0x1B);
                g_ScenarioState.step_05 = 0x13;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 2) {
                Party_AddZenny(1000, 0);
                g_ScriptVars[0]         = 3;
                g_ScenarioState.step_05 = 0x14;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 4) {
                g_ScenarioState.step_05 = 0x15;
                func_801C16B8();
                g_ScenarioState.flags_01 ^= 1;
                SYS_ClearFlag(g_SceneFlags, 0x15);
                SYS_ClearFlag(g_SceneFlags, 0x17);
                Game_RequestAreaChange(0x57, TO_COORD(49), TO_COORD(45), 4);
            }
            break;
        case 21:
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            SCENARIO_RETURN_TO_START();
            break;
        case 25:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step_05 = 0x1A;
            }
            break;
        case 26:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_AreaDrawFlags         = 0;
                g_ScenarioState.step_05 = 0x1B;
                g_ScenarioState.flags_01 |= 1;
                Game_RequestAreaChange(0x5C, TO_COORD(14), TO_COORD(60), 0x80);
            }
            break;
        case 27:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_001, 0x1C);
            break;
        case 28:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                func_801C601C(0);
                g_ScenarioState.step_05 = 0x1D;
            }
            break;
        case 29:
            if (g_ScriptVars[0] == 2) {
                g_GameStateIndex        = 7;
                D_8018E244              = 0;
                g_AreaDrawFlags         = 0;
                g_ScenarioState.step_05 = 0x1E;
            }
            break;
        case 30:
            if (g_GameStateIndex == 0) {
                g_ScenarioState.step_05 = 0x1F;
            }
            break;
        case 31:
            if (D_80144DF2 == 0) {
                g_ScenarioState.step_05 = 0x20;
            } else if (D_80144DF5 != 0) {
                g_ScenarioState.step_05 = 0x28;
            } else {
                g_ScenarioState.step_05 = 0x20;
            }
            break;
        case 32:
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 0x21;
            SYS_SetFlag(g_SceneFlags, 0x17);
            Game_RequestAreaChange(0x5C, TO_COORD(25), TO_COORD(60), 0x82);
            break;
        case 35:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]         = 1;
                g_ScenarioState.step_05 = 0x24;
                func_801BE1B0(3);
            }
            break;
        case 36:
            if (g_ScriptVars[0] == 3) {
                g_ScenarioState.step_05 = 0x25;
                func_801C16B8();
                g_ScenarioState.flags_01 ^= 1;
                SYS_ClearFlag(g_SceneFlags, 0x15);
                SYS_ClearFlag(g_SceneFlags, 0x17);
                Game_RequestAreaChange(0x57, TO_COORD(49), TO_COORD(45), 4);
            }
            break;
        case 37:
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            SCENARIO_RETURN_TO_START();
            break;
        case 40:
            g_ScenarioState.step_05 = 0x2D;
            g_ScriptVars[2]         = 2;
            SYS_SetFlag(g_SceneFlags, 0x1A);
            SYS_SetFlag(g_SceneFlags, 0x1B);
            Game_RequestAreaChange(0x5C, TO_COORD(25), TO_COORD(60), 0x81);
            g_GamePrevSelection = 0x3C;
            break;
        case 50:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step_05 = 0x33;
                g_ScriptVars[2]         = 1;
                g_ScenarioState.flags_01 |= 1;
                Game_RequestAreaChange(0x5C, TO_COORD(25), TO_COORD(60), 0x88);
            }
            break;
        case 11:
        case 15:
        case 33:
        case 45:
        case 51:
            if (g_ScriptVars[0] == 3) {
                Game_ClearScriptActive();
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 60:
            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            *state                  = 7;
            D_8018E244              = 0;
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 0x3D;
            break;
        case 61:
            if (g_GameStateIndex == 0) {
                g_ScenarioState.step_05 = 0x3E;
            }
            break;
        case 62:
            if (D_80144DF2 == 0) {
                g_ScenarioState.step_05 = 0x20;
            } else if (D_80144DF5 != 0) {
                g_ScenarioState.step_05 = 0x28;
            } else {
                g_ScenarioState.step_05 = 0x20;
            }
            break;
    }
}
