#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA34C(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_UIMessageRequest != 0x12) {
                break;
            }
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step = 0;
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case 2:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            g_ScenarioState.timer_06 = 10;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 3;
            break;
        case 3:
            if (g_ScenarioState.timer_06 == 0) {
                g_GameFlags |= 0x80;
                Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(40), TO_COORD(34), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                g_GameRequestType    = 1;
                g_GameEntryMode      = 0xFF;
                g_ScenarioState.step = 4;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_GameFlags &= ~0x80;
            Game_RequestAreaChange(AREA_ID_GENMEL, TO_COORD(41), TO_COORD(37), FACING_DOWN);
            g_GameRequestType    = 0xFE;
            g_GameEntryMode      = 0;
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Game_SetScriptActive();
            Party_BattlersHide();
            SCENARIO_MESSAGE_WAIT(MSG_SCENA03_010, 6);
            break;
        case 6:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_ModeSet(1);
            g_AreaDrawFlags          = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 7;
            break;
        case 7:
            if (g_ScenarioState.timer_06 == 0) {
                Area_ScrollStartRoute(1);
                g_ScenarioState.step = 8;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 8:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2EC;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x376;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x80;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                Game_RequestAreaChange(AREA_ID_GENMEL, TO_COORD(11), TO_COORD(97), FACING_DOWN);
                g_GameRequestType    = 0xFE;
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Party_BattlersShow();
            SCENARIO_MESSAGE_WAIT(MSG_SCENA03_011, 11);
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            UI_ModeSet(1);
            Scene_RunScenario(1);
            Scene_SetupParty(3);
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x1B8;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xB4;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x60;
            }
            g_ScenarioState.step = 13;
            break;
        case 13:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x60;
            }
            g_ScenarioState.step = 14;
            break;
        case 14:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x19);
            Game_RequestAreaChange(AREA_ID_GENMEL, TO_COORD(23), TO_COORD(54), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
            g_ScenarioState.step = 15;
            break;
        case 15:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x1A);
            g_ScenarioState.step = 0;
            Game_ClearScriptActive();
            break;
        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_UIMessageRequest != 0x1F) {
                break;
            }
            g_ScenarioState.step = 17;
            break;
        case 17:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            break;
    }
}
