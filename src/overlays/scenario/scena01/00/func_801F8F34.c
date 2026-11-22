#include "scena01_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8F34(void) {
    switch (g_ScenarioState.step) {
        case 0:
            Area_ScrollStartRoute(0);
            Scene_SetupParty(0);
            g_ScenarioState.step = 1;
            break;
        case 1:
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ += 0x20;
            if (++g_ScriptVars[3] < 0x50) {
                break;
            }
            g_AreaCameraOffsetZ      = 0xA00;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 0x1F) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x20;
            if (++g_ScriptVars[3] < 0x50) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 0x28) {
                break;
            }
            UI_CursorDraw(0xD2, 0x3C, 0);
            if (g_PadStates[0].pressed == 0) {
                break;
            }
            g_ScriptVars[0]      = 0x29;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x2A) {
                break;
            }
            if (g_AreaCameraMoving != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 2);
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 10:
            Scene_SetupParty(1);
            Area_ScrollStartRoute(5);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaScrollTargetX  = 0x210000;
            g_AreaCameraSpeed    = 0x20;
            g_ScenarioState.step = 0xC;
            g_AreaScrollTargetY  = D_80145EC8;
            break;
        case 12:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_ScenarioState.step = 0xD;
            break;
        case 13:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_AreaScrollTargetX         = 0x160000;
            g_AreaCameraSpeed           = 0x20;
            g_AreaScrollTargetY         = D_80145EC8;
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] == GAME_NONE) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x1CE;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x26E;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step                                        = 0xE;
            break;
        case 14:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]      = 4;
            g_ScenarioState.step = 0x11;
            break;
        case 17:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            SND_BGMPlay(0x14, 0x64, 8);
            g_ScenarioState.step = 0x12;
            break;
        case 18:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] == GAME_NONE) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step                                        = 0x13;
            break;
        case 19:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] == GAME_NONE) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x35A;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step                                        = 0x14;
            break;
        case 20:
            if (g_ScriptVars[0] != 0x18) {
                break;
            }
            SND_SeqStop(0, 1);
            SND_BGMPlay(0x13, 0x64, 8);
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] == GAME_NONE) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
            g_ScenarioState.step                                        = 0x15;
            g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            break;
        case 21:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags != 0) {
                break;
            }
            g_ScriptVars[3]      = 0;
            g_ScriptVars[0]      = 0x19;
            g_ScenarioState.step = 0x16;
            g_GameFlags |= 8;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x22) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 3);
            g_GameFlags ^= 8;
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            SCENARIO_RETURN_TO_START();
            break;
    }
}
