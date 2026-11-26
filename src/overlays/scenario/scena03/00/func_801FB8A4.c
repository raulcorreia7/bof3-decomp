#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB8A4(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_UiMessageRequest != 1) {
                break;
            }
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case 2:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 3;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 3:
            SND_StartDecrescendo(0, 0, 100, 0x20);
            func_801BE1B0(0);
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x344;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x192;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x10;
            }
            g_ScenarioState.timer_06 = 0x10;
            g_ScenarioState.step     = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 0x13) {
                break;
            }
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraOffsetZ += 0x40;
            } else {
                g_ScenarioState.timer_06 = 6;
                g_ScenarioState.step     = 6;
            }
            break;
        case 6:
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 7;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 7:
            if (g_ScenarioState.timer_06 == 0x20) {
                SND_SEPlay(0x201);
                g_ScenarioState.step = 8;
                break;
            }
            if ((g_ScenarioState.timer_06 & 3) == 3) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC3B4();
            g_ScenarioState.timer_06++;
            break;
        case 8:
            if (g_ScenarioState.timer_06 == 0x30) {
                g_ScenarioState.step = 9;
                break;
            }
            if (g_ScenarioState.timer_06 & 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 9:
            if (g_ScenarioState.timer_06 == 0x50) {
                SND_SEPlay(0x201);
                g_ScenarioState.step = 10;
                break;
            }
            if (g_ScenarioState.timer_06 & 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 10:
            if (g_ScenarioState.timer_06 == 0x90) {
                SND_SEPlay(0x204);
                g_ScenarioState.step        = 11;
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x23;
                }
                break;
            }
            if (g_ScenarioState.timer_06 & 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 11:
            if (g_ScenarioState.timer_06 == 0xA0) {
                g_ScenarioState.step = 12;
                SND_SEPlay(0x201);
                SND_SEPlay(0x205);
                break;
            }
            if (g_ScenarioState.timer_06 & 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 12:
            if (g_ScenarioState.timer_06 == 0x110) {
                SND_SEPlay(0x202);
                SND_SEPlay(0x206);
                g_ScenarioState.step = 13;
                break;
            }
            if (g_ScenarioState.timer_06 & 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 13:
            if (g_ScenarioState.timer_06 == 0x130) {
                g_ScenarioState.step = 14;
                break;
            }
            if ((g_ScenarioState.timer_06 & 3) == 1) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            func_801FC410();
            g_ScenarioState.timer_06++;
            break;
        case 14:
        case 15:
            if (g_ScriptVars[0] == 0x15) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                          = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x3C;
                }
                g_ScenarioState.step = 16;
            } else if (g_ScriptVars[0] < 0x15) {
                func_801FC1D0(0);
                func_801FC1D0(1);
            }
            break;
        case 16:
            if (g_ScriptVars[0] != 0x17) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_BGMFadeOut(g_SndBGMId, 100, 8);
            g_ScenarioState.step = 17;
            break;
        case 17:
            g_AreaScrollTargetX = TO_COORD(36);
            g_AreaScrollTargetY = TO_COORD(74);
            Area_InitMapRenderer();
            g_ScenarioState.timer_06 = 10;
            g_ScenarioState.step     = 18;
            break;
        case 18:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                UI_ModeSet(1);
                g_ScriptVars[0]++;
                SND_BGMPlay(0x49, 100, 8);
                g_ScenarioState.step = 19;
            }
            break;
        case 19:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type = 0x25;
            }
            g_ScenarioState.step = 20;
            break;
        case 20:
            if (g_ScriptVars[0] != 0x27) {
                break;
            }
            SND_BGMFadeOut(0x49, 100, 8);
            SND_BGMPlay(0x51, 100, 8);
            SYS_SetFlag(g_SceneFlags, 0x1E);
            SYS_SetFlag(&g_SaveData.found_genes, 6);
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            func_801A78F8();
            break;
    }
}
