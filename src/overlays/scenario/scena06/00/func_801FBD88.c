#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FBD88(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (!WINDOW_EFFECT_BUSY()) {
                MESSAGE_START_WAIT(MSG_000);
                Area_StartScrollRoute(0);
                Scene_SetupParty(0);
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(5);
                g_AreaDrawFlags         = 0x1F;
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                g_ScriptVars[0]         = 1;
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x252;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0xA0;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                g_ScenarioState.step_05                                     = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 2) {
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x35A;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x3FA;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x8C;
                    g_ScenarioState.step_05                                     = 5;
                    g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
                }
            }
            break;
        case 5:
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x100;
            if (++g_ScriptVars[3] >= 0xD) {
                g_AreaCameraOffsetZ      = -0x280;
                g_AreaCameraRefreshCount = 2;
                g_ScriptVars[3]          = 0;
                g_ScriptVars[0]          = 3;
                g_ScenarioState.step_05  = 7;
            }
            break;
        case 6:
            break;
        case 7:
            if (g_ScriptVars[0] == 4) {
                g_ScenarioState.step_05 = 8;
                SYS_SetFlag(g_SceneFlags, 5);
                Game_RequestAreaChange(0x37, 0x250000, 0x130000, 0x81);
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x16) {
                UI_SetMode(0xD);
                g_ScenarioState.step_05 = 9;
            }
            break;
        case 9:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                g_ScriptVars[0] = 0x17;
                SCENARIO_MESSAGE_WAIT(MSG_020, 0xA);
                SND_FadeOutSequence(0, 1, 4, 0x1E);
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_StartXAStream(3, 1);
                g_ScenarioState.step_05 = 0xB;
            }
            break;
        case 11:
            if ((u8)SND_IsXAIdle() != 0) {
                func_801C1DF0(5);
                g_ScenarioState.step_05 = 0xC;
                SYS_SetFlag(g_SceneFlags, 6);
            }
            break;
        case 12:
            if (g_GameStateIndex == 0) {
                g_ScenarioState.step_05 = 0xD;
                Game_RequestAreaChange(0x37, 0x160000, 0x130000, 0x82);
                SND_PlayBGM(0x79, 0x64, 8);
            }
            break;
        case 13:
            g_AreaDrawFlags = 0x1F;
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}
#else
INCLUDE_ASM(func_801FBD88);
#endif
