#include "scena03_00.h"
#include "area/map.h"

MATCH void func_801FB268(void) {
    u8  slot;
    s8  staged_index;
    s8  staged;
    s8* staged_slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScriptVars[0] = 0;
            Scene_SetupParty(4);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 2) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            Game_RequestAreaChange(0x63, 0x68000, 0x230000, 1);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_ScenarioState.step = 3;
            break;
        case 3:
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] == 7) {
                Game_RequestAreaChange(0x63, 0x230000, 0x510000, 0x85);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x12) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x32E;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x38;
                }
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x16) {
                staged                 = Actor_FindFreeSpawned();
                g_ScenarioState.unk_03 = staged;
                staged_slot            = (s8*)&g_ScenarioState.unk_03;
                if (staged != -1) {
                    g_SpawnedActors[staged].header.flags      = ACTOR_FLAG_IN_USE;
                    staged_index                              = *staged_slot;
                    g_SpawnedActors[staged_index].type        = 0x22;
                    staged_index                              = *staged_slot;
                    g_SpawnedActors[staged_index].pos.x.fixed = 0x230000;
                    FAKE_BARRIER(); /* FAKE: retain the staged slot reload after x. */
                    staged_index                              = *staged_slot;
                    g_SpawnedActors[staged_index].pos.y.fixed = 0x4F0000;
                    FAKE_BARRIER(); /* FAKE: retain the staged slot reload after y. */
                    staged_index                              = *staged_slot;
                    g_SpawnedActors[staged_index].pos.z.fixed = TO_COORD(0x480);
                }
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x18) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x38;
                }
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x27) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            g_ScenarioState.timer_06 = 0xA;
            g_ScenarioState.step     = 0xA;
            g_ScriptVars[0]++;
            break;
        case 10:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 0xB;
            g_ScriptVars[0]++;
            break;
        case 11:
            if (g_ScriptVars[0] == 0x2F) {
                g_ScenarioState.step = 0xC;
            }
            break;
        case 12:
            g_ScenarioState.step = 0xD;
            break;
        case 13:
            if (g_ScriptVars[0] == 0x34) {
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                SYS_SetFlag(g_SceneFlags, 0x1D);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                g_GameFlags &= ~0x80;
            }
            break;
    }
}
