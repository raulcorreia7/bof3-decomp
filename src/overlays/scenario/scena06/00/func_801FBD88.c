#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBD88(void) {
    SpawnedActor* actor;
    u8            slot;
    u8            i;

    switch (g_ScenarioState.step_05) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_026, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 0;
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 5:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_027, 6);
            break;
        case 6:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                actor               = &g_SpawnedActors[slot];
                actor->header.flags = 1;
                actor->type         = 0x4B;
            }
            Scene_SetupParty(6);
            g_AreaSceneMode = 1;
            SYS_SetFlag(g_SceneEventFlags, 7);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 7));
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
            g_ScenarioState.step_05 = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 0x29) {
                break;
            }
            UI_ModeSet(0xF);
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            UI_ModeSet(0x10);
            Scene_SetupParty(7);
            Area_ScrollStartRoute(2);
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0]         = 0x2A;
            g_ScenarioState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x2D) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x32E;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x50;
                g_ScenarioState.step_05                                     = 13;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 13:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags != 0) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x28;
                g_ScenarioState.step_05                                     = 14;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 14:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags != 0) {
                break;
            }
            g_ScriptVars[0]         = 0x2F;
            g_ScriptVars[3]         = 0;
            g_ScenarioState.step_05 = 17;
            break;
        case 17:
            if (g_ScriptVars[0] != 0x35) {
                break;
            }
            SND_SeqStop(0, 2);
            SND_BGMPlay(0x5C, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step_05 = 18;
            break;
        case 18:
            if (g_ScriptVars[0] != 0x42) {
                break;
            }
            SND_SeqFadeOut(0, 1, 4, 0x1E);
            SND_XAStartStream(2, 1);
            g_ScenarioState.step_05 = 19;
            break;
        case 19:
            if ((u8)SND_XAIsIdle() == 0) {
                break;
            }
            SND_BGMPlay(0x5C, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScriptVars[0]         = 0x43;
            g_ScenarioState.step_05 = 20;
            break;
        case 20:
            if (g_ScriptVars[0] != 0x47) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 2) {
                    UI_MessageStartArea(MSG_SCENA06_037);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 5) {
                    UI_MessageStartArea(MSG_SCENA06_036);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 1) {
                    UI_MessageStartArea(MSG_SCENA06_035);
                }
            }
            g_GameStateIndex        = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step_05 = 21;
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0]         = 0x48;
            g_ScenarioState.step_05 = 22;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x49) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x2C);
            Item_Add(0, 0x57, 1, 0);
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 30:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_038, 1);
            break;
    }
}
