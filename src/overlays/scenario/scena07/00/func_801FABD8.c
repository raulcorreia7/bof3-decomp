#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FABD8(void) {
    u16 flags;

    switch (g_ScenarioState.step_05) {
        case 0:
            Message_StartAreaMessage(0x11);
            g_GameStateIndex        = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step_05 = 1;
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(0);
                if (g_SndBGMId != 0xFF) {
                    SND_FadeOutBGM(g_SndBGMId, 0x64, 8);
                }
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.timer_06 = 0x1E;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step_05  = 5;
            }
            break;
        case 5:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.flags_01 |= 1;
                func_801C1DF0(0);
                func_8019FA28(0xAF, 0x240000, 0x1E0000, 0x81);
                g_GameArea.entry_mode   = 0xFF;
                g_GameArea.request_type = 0xFF;
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 6:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(1);
                g_ScenarioState.step_05 = 7;
            }
            break;
        case 7:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step_05  = 8;
            }
            break;
        case 8:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScriptVars[0]         = 1;
                g_ScenarioState.step_05 = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 3) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x31E;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0xE0;
                    g_ScenarioState.step_05                                     = 0xA;
                }
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 4 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_PlayBGM(0x60, 0x64, 8);
                g_ScenarioState.step_05 = 0xB;
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 5) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x70;
                    g_ScenarioState.step_05                                     = 0xC;
                }
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0xA) {
                SND_FadeOutBGM(0x60, 0x64, 8);
                SND_PlayBGM(0x63, 0x64, 8);
                g_ScenarioState.step_05 = 0xD;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 0xB) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x35A;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x48;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x30;
                    g_ScenarioState.timer_06                                    = 0x30;
                    g_ScenarioState.step_05                                     = 0xE;
                }
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 0xC) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x31;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].scene_step     = -0x380;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x40;
                    g_ScenarioState.step_05                                     = 0xF;
                }
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 0xD) {
                UI_SetMode(0);
                g_ScenarioState.step_05 = 0x10;
            }
            break;
        case 16:
            if (g_UiWindowEffectBusy == 0) {
                SND_FadeOutBGM(0x63, 0x64, 8);
                g_AreaDrawFlags         = 0;
                g_ScenarioState.step_05 = 0x11;
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 0x12) {
                UI_SetMode(1);
                g_AreaDrawFlags          = 0x1F;
                g_AreaCameraAngle.vx     = -0x2AA;
                g_AreaCameraAngle.vz     = 0x200;
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraAngle.vy     = 0;
                g_AreaCameraOffsetZ      = 0;
                g_ScenarioState.step_05  = 0x12;
            }
            break;
        case 18:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.step_05 = 0x13;
                g_ScriptVars[0]++;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x22) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x38;
                    g_ScenarioState.step_05                                   = 0x14;
                }
            }
            break;
        case 21:
            UI_SetMode(0);
            g_ScenarioState.step_05 = 0x16;
            break;
        case 22:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                UI_SetMode(1);
                g_ScenarioState.step_05 = 0x19;
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 0x45) {
                SND_PlaySE(0x20C);
                func_801BFE34(0x240000, 0x1C8000, 0x1D);
                g_ScenarioState.step_05 = 0x1A;
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 0x46) {
                func_801C7A54(0x1D);
                SYS_SetFlag(g_SceneFlags, 1);
                g_ScenarioState.step_05 = 0x1B;
            }
            break;
        case 28:
            SND_PlaySE(0x201);
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
            break;
    }
}
