#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Word 1 of the overlay's secondary-state handler run: the step sequence of primary state 6. */
MATCH void func_801F9F0C(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[2]      = 1;
            g_ScriptVars[1]      = 0;
            g_SceneState.step_05 = 1;
            g_GameFlags ^= 0x20;
            Game_RequestAreaChange(0xBC, 0x68000, 0x598000, 0x80);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            g_AreaDrawFlags = 0x1F;
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 2;
            break;
        case 2: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 5) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x28);
            *progress            = 0;
            g_ScriptVars[2]      = 1;
            g_SceneState.step_05 = 3;
            SYS_SetFlag(g_SceneFlags, 0x15);
            Game_RequestAreaChange(0x79, 0x238000, 0x310000, 6);
            g_GamePrevSelection = 0xFF;
            break;
        }
        case 3:
            g_AreaSceneMode             = 1;
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if ((g_ScratchPad.cells.bytes[0] & 0xFF) == 0xFF) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x370;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 4;
            g_SceneState.step_05                                        = 4;
            g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            break;
        case 4: {
            u8* record_index = &g_ScriptVars[3];
            if (g_SpawnedActors[*record_index].header.flags != 0) {
                break;
            }
            *record_index        = 0;
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 5;
            break;
        }
        case 5: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 5) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 2;
            g_ScriptVars[1]      = 1;
            g_SceneState.step_05 = 6;
            Game_RequestAreaChange(0xBC, 0x68000, 0x598000, 0x81);
            g_GamePrevSelection = 0x8F;
            break;
        }
        case 6: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 0xA) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 3;
            g_ScriptVars[1]      = 2;
            g_SceneState.step_05 = 7;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0x100000, 0x490000, 0x82);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 7:
            Area_StartScrollRoute(1);
            g_SceneState.step_05 = 8;
            break;
        case 8: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 2) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 4;
            g_ScriptVars[1]      = 3;
            g_SceneState.step_05 = 9;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0x3C0000, 0x2F0000, 0x83);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 9:
            Area_StartScrollRoute(2);
            g_SceneState.step_05 = 0xA;
            break;
        case 10: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 4;
            g_ScriptVars[1]      = 4;
            g_SceneState.step_05 = 0xB;
            g_GamePrevSelection  = 0xFF;
            g_GameFlags ^= 8;
            Game_RequestAreaChange(0xBC, 0x68000, 0x88000, 0x84);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 11: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[1]      = 5;
            g_SceneState.step_05 = 0xC;
            g_ScriptVars[2]      = 0;
            g_GamePrevSelection  = 0xFF;
            g_GameFlags ^= 8;
            Game_RequestAreaChange(0xBC, 0x78000, 0x1F0000, 0x85);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 12: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 2) {
                break;
            }
            SND_PlayCue(0x20C);
            *progress            = 0;
            g_ScriptVars[2]      = 4;
            g_ScriptVars[1]      = 6;
            g_SceneState.step_05 = 0xD;
            g_GamePrevSelection  = 0xFF;
            g_GameFlags |= 8;
            Game_RequestAreaChange(0xBC, 0x120000, 0x340000, 0x89);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 13:
            Area_StartScrollRoute(3);
            g_SceneState.step_05 = 0xE;
            break;
        case 14: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 3) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[1]      = 7;
            g_SceneState.step_05 = 0xF;
            g_ScriptVars[2]      = 0;
            g_GamePrevSelection  = 0xFF;
            g_GameFlags ^= 8;
            Game_RequestAreaChange(0xBC, 0x1D8000, 0x98000, 0x8A);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 15: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[1]      = 8;
            g_SceneState.step_05 = 0x10;
            g_ScriptVars[2]      = 0;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0x40000, 0x3E0000, 0x8B);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 16: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_SceneState.step_05 = 0x11;
            g_ScriptVars[2]      = 0;
            g_ScriptVars[1]      = 0;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0xA0000, 0x5A0000, 0x8C);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 17: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 5;
            g_ScriptVars[1]      = 9;
            g_SceneState.step_05 = 0x12;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0x120000, 0x400000, 0x8D);
            g_GamePrevSelection = 0x90;
            break;
        }
        case 18: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 3) {
                break;
            }
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if ((g_ScratchPad.cells.bytes[0] & 0xFF) == 0xFF) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x7A;
            *progress                                                 = 4;
            g_SceneState.step_05                                      = 0x13;
            break;
        }
        case 19:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_FadeOutSequence(0, 1, 4, 0x1E);
            UI_SetMode(0xD);
            g_SceneState.step_05 = 0x14;
            break;
        case 20:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            g_ScriptVars[2]      = 6;
            g_ScriptVars[0]      = 0;
            g_ScriptVars[1]      = 0;
            g_SceneState.step_05 = 0x16;
            SYS_SetFlag(g_SceneFlags, 0x29);
            Game_RequestAreaChange(0xBC, 0x120000, 0x400000, 0x8E);
            g_GamePrevSelection = 0xFF;
            break;
        case 22:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 7;
            g_ScriptVars[3] = 0;
            g_GameFlags |= 0x20;
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
