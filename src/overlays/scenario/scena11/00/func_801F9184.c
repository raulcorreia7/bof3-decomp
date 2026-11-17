#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9184(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScenarioState.step_05 = 1;
            SYS_SetFlag(g_SceneFlags, 0xE);
            Game_RequestAreaChange(0x65, 0x240000, 0x250000, 0x80);
            break;

        case 1: {
            u8 object_index;

            Area_StartScrollRoute(0);
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZHalf -= 0x500;

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x1A2;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 4;
                g_ScenarioState.step_05                                     = 2;
            }
            break;
        }

        case 2:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 3;
            break;

        case 3: {
            u8 object_index;

            g_AreaScrollTargetX = 0x220000;
            g_AreaScrollTargetY = 0x230000;
            g_AreaCameraStep    = 4;

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x31;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].scene_step     = 0;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xFF;
                g_ScenarioState.step_05                                     = 4;
            }
            break;
        }

        case 4:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]         = 1;
            g_ScenarioState.step_05 = 6;
            break;

        case 6: {
            u8 object_index;

            if (g_ScriptVars[0] != 4) {
                break;
            }

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2EC;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x0A;
                g_ScenarioState.step_05                                     = 7;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        }

        case 7: {
            u8* claimed;

            claimed = &g_ScriptVars[3];
            if (g_SpawnedActors[*claimed].header.flags == 0) {
                g_ScriptVars[0]         = 5;
                *claimed                = 0;
                g_ScenarioState.step_05 = 8;
            }
        }
            /* Falls into the sub-state 8 body. */
        case 8: {
            u8 object_index;

            if (g_ScriptVars[0] != 0xA) {
                break;
            }

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x0A;
                g_ScenarioState.step_05                                     = 9;
            }
            break;
        }

        case 9:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            UI_SetMode(0xD);
            g_ScenarioState.step_05 = 0xA;
            break;

        case 10:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 0xB;
            break;

        case 11:
            Message_StartAreaMessage(MSG_004);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 0xC;
            break;

        case 12:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step_05 = 0xD;
            g_ScriptVars[0]         = 0;
            g_ScriptVars[2]         = 1;
            Game_RequestAreaChange(0x65, 0x490000, 0x90000, 0x81);
            break;

        case 13: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 0x14) {
                break;
            }
            *progress               = 0;
            g_ScriptVars[2]         = 1;
            g_ScenarioState.step_05 = 0xE;
            Game_RequestAreaChange(0x84, 0x530000, 0x1B0000, 0x83);
            break;
        }

        case 14: {
            u8 object_index;

            SND_PlaySE(0x200);
            Area_StartScrollRoute(1);
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZHalf -= 0x780;

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x3C8;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x258;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 4;
                g_ScenarioState.step_05                                     = 0xF;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }

            Area_SetCellPalette(0x53, 0x1B);

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags               = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type        = 0x18;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.mode = 0x5F;
            }

            g_AreaSceneMode = 0x23;
            break;
        }

        case 15: {
            u8* claimed;

            claimed = &g_ScriptVars[3];
            if (g_SpawnedActors[*claimed].header.flags != 0) {
                break;
            }
            *claimed = 0;
            Message_StartAreaMessage(MSG_026);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 0x10;
            break;
        }

        case 16:
            if (g_GameStateIndex == 2) {
                break;
            }
            UI_SetMode(0xD);
            g_ScenarioState.step_05 = 0x11;
            break;

        case 17:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_ScriptVars[0]         = 1;
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 0x12;
            break;

        case 18: {
            u8 object_index;

            if (g_ScriptVars[0] != 2) {
                break;
            }

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x31;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x370;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x258;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].scene_step     = 0x580;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                g_ScenarioState.step_05                                     = 0x13;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        }

        case 19: {
            u8* claimed;

            claimed = &g_ScriptVars[3];
            if (g_SpawnedActors[*claimed].header.flags != 0) {
                break;
            }
            g_ScriptVars[0]         = 3;
            *claimed                = 0;
            g_ScenarioState.step_05 = 0x14;
            break;
        }

        case 20: {
            u8 object_index;

            if (g_ScriptVars[0] != 4) {
                break;
            }

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x256;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xE2;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                g_ScenarioState.step_05                                     = 0x15;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        }

        case 21: {
            u8 object_index;

            if (g_ScriptVars[0] != 6) {
                break;
            }
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags != 0) {
                break;
            }
            g_ScriptVars[3] = 0;

            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;

            if (object_index != 0xFF) {
                g_SpawnedActors[object_index].header.flags                  = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x31;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x386;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xE2;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].scene_step     = 0;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                g_ScenarioState.step_05                                     = 0x16;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        }

        case 22: {
            u8* claimed;

            claimed = &g_ScriptVars[3];
            if (g_SpawnedActors[*claimed].header.flags != 0) {
                break;
            }
            g_ScriptVars[0]         = 7;
            *claimed                = 0;
            g_ScenarioState.step_05 = 0x1B;
            break;
        }

        case 27: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 0x16) {
                break;
            }
            *progress               = 0;
            g_ScriptVars[2]         = 2;
            g_ScriptVars[1]         = 0;
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 0x1D;
            SYS_SetFlag(g_SceneFlags, 0xF);
            SND_PlaySE(0x201);
            Game_RequestAreaChange(0x84, 0x50000, 0x460000, 0x84);
            break;
        }

        case 29: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress               = 2;
            g_ScenarioState.step_05 = 0x1F;
            break;
        }

        case 31: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 3) {
                break;
            }
            *progress               = 4;
            g_ScenarioState.step_05 = 0x21;
            break;
        }

        case 33: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 0x0A) {
                break;
            }
            *progress               = 0;
            g_ScenarioState.step_05 = 0x22;
            SYS_SetFlag(g_SceneFlags, 0x10);
            Game_RequestAreaChange(0x83, 0x200000, 0x2F0000, 0x87);
            break;
        }

        case 34:
            Area_StartScrollRoute(1);
            g_ScenarioState.step_05 = 0x23;
            break;

        case 35:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(4);
            g_ScenarioState.step_05 = 0x24;
            break;

        case 36:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_ScriptVars[2]         = 2;
            g_ScriptVars[0]         = 0;
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 0x25;
            break;

        case 37:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step_05 = 0x26;
            SYS_SetFlag(g_SceneFlags, 0x11);
            Game_RequestAreaChange(0x83, 0x50000, 0x5D0000, 0x88);
            break;

        case 38:
            Area_StartScrollRoute(2);
            g_ScenarioState.step_05 = 0x27;
            break;

        case 39: {
            u8* progress;

            progress = &g_ScriptVars[0];
            if (*progress != 0x15) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x12);
            Game_ClearScriptActive();
            *progress                = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        }
    }
}
