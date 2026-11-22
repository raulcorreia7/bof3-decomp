#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F90C0(void) {
    u8 count;
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            Scene_SetupParty(3);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_ScenarioState.step = 2;
            g_ScriptVars[2]      = 2;
            SYS_SetFlag(g_SceneFlags, 18);
            Game_RequestAreaChange(AREA_ID_RHAPALA_DOCK, TO_COORD(46), TO_COORD(46), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
            break;
        case 2:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_056, 3);
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_ModeSet(5);
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -528;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 754;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                g_ScriptVars[0]                                             = 3;
                g_ScenarioState.step                                        = 6;
            }
            break;
        case 6:
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x40;
            count           = g_ScriptVars[3] + 1;
            g_ScriptVars[3] = count;
            if (count < 18) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x13) {
                break;
            }
            Area_ScrollStartRoute(0);
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -682;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 512;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x1E;
                g_ScenarioState.step                                        = 8;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 8:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags == 0) {
                g_ScriptVars[0]      = 0x14;
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            g_ScenarioState.step = 10;
            SYS_SetFlag(g_SceneFlags, 19);
            Game_RequestAreaChange(AREA_ID_RHAPALA_DOCK, TO_COORD(44), TO_COORD(41), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            g_GamePrevSelection = 0x42;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x22) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 16);
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
        case 20:
            Scene_SetupParty(6);
            Area_ScrollStartRoute(1);
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_AreaCameraSpeed    = 0x20;
            g_ScenarioState.step = 22;
            g_AreaScrollTargetX  = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY  = g_Game.members[0].pos.y.fixed;
            break;
        case 22:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]      = 5;
            g_ScenarioState.step = 23;
            break;
        case 23:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            Party_AddZenny(1000, 0);
            g_ScriptVars[0]      = 8;
            g_ScenarioState.step = 24;
            break;
        case 24:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 20);
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
        case 30:
            g_ScenarioState.step = 31;
            Game_RequestAreaChange(AREA_ID_RHAPALA_DOCK, TO_COORD(82), TO_COORD(51), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_LEFT);
            break;
        case 31:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 32;
            break;
        case 32:
            if (g_ScriptVars[0] != 0x36) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}
