#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB5BC(void) {
    u8  slot;
    u8  v;
    u8* step;

    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScenarioState.step_05 = 1;
            SYS_SetFlag(g_SceneFlags, 0x19);
            Game_RequestAreaChange(AREA_ID_MCNEIL_BEFORE_NUE, TO_COORD(2), TO_COORD(0x14), AREA_ENTRY_MAP_LOADING);
            break;
        case 1:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[slot].header.flags                          = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x31E;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step_05                                     = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[slot].header.flags                          = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step_05                                     = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x12) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x1A);
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            SCENARIO_RETURN_TO_START();
            break;
        case 10:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA01_032, 11);
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 15:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SetupParty(1);
                g_ScenarioState.step_05 = 0x10;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 0x19) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step_05 = 0x11;
            }
            break;
        case 17:
            g_ScriptVars[2]         = 0;
            g_ScenarioState.step_05 = 0x12;
            SYS_SetFlag(g_SceneFlags, 0x1B);
            Game_RequestAreaChange(AREA_ID_FARM_BEFORE_NUE, TO_COORD(0xF), TO_COORD(0x1F), AREA_ENTRY_MAP_LOADING);
            break;
        case 18:
            step                     = &g_ScriptVars[3];
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x40;
            v     = *step + 1;
            *step = v;
            if (v < 0x2E) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            *step                    = 0;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            g_ScriptVars[0]         = 2;
            g_ScenarioState.step_05 = 0x13;
            break;
        case 19:
            if (g_ScriptVars[0] != 0x19) {
                break;
            }
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 0x1C);
            g_GameFlags ^= 0x60;
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            SCENARIO_RETURN_TO_START();
            break;
    }
}
