#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7C6C(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(3);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 4) {
                SYS_SetFlag(g_SceneFlags, 4);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_066, 6);
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0xF;
                switch (g_Game.members[0].facing) {
                    case FACING_UP_RIGHT:
                        Scene_SetupParty(4);
                        g_ScenarioState.step = 11;
                        break;
                    case FACING_RIGHT:
                        Scene_SetupParty(5);
                        g_ScenarioState.step = 11;
                        break;
                    case FACING_DOWN_RIGHT:
                        Scene_SetupParty(6);
                        g_ScenarioState.step = 11;
                        break;
                }
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x14) {
                SYS_SetFlag(g_SceneFlags, 5);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 15:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0x19;
                Scene_SetupParty(8);
                g_ScenarioState.step = 16;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 0x1A) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 60;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                    g_ScenarioState.step                                        = 17;
                    g_ScriptVars[1]                                             = g_ScratchPad.cells.bytes[0];
                }
            }
            break;
        case 17:
            if (g_SpawnedActors[g_ScriptVars[1]].header.flags == 0) {
                g_ScriptVars[0]      = 0x1B;
                g_ScriptVars[1]      = 0;
                g_ScenarioState.step = 18;
            }
            break;
        case 18:
            if (g_ScriptVars[0] == 0x1C) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 512;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                    g_ScenarioState.step                                        = 19;
                }
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x1E) {
                SYS_SetFlag(g_SceneFlags, 7);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
