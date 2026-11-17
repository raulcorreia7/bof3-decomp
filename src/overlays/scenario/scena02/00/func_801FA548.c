#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA548(void) {
    switch (g_SceneState.step_05) {
        case 0:
            SND_StopSequence(0, 0);
            SND_PlayBGM(0x25, 0x64, 8);
            SCENE_MESSAGE_WAIT(MSG_020, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Area_StartScrollRoute(2);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                Scene_SetupParty(5);
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 6) {
                SND_StopSequence(0, 1);
                g_SceneState.step_05 = 4;
                D_80146258 |= GAME_FLAG_SCROLL_LOCK;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0xE) {
                SND_StartXAStream(1, 1);
                SND_PlaySE(0x203);
                g_ScriptVars[1]      = 0;
                g_ScriptVars[3]      = 0;
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            func_801FCBDC(0xA);
            if (g_ScriptVars[0] == 0x14) {
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraOffsetY      = 0;
                g_ScriptVars[1]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScriptVars[0]          = 0x15;
                g_SceneState.step_05     = 0xF;
                SND_PlaySE(0x204);
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 0x19) {
                SND_PlaySE(0x201);
                UI_SetMode(0xF);
                g_SceneState.step_05 = 0x10;
            }
            break;
        case 16:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]      = 0x1A;
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 0x11;
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 0x1B) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(0x10);
                g_SceneState.step_05 = 0x12;
                func_801BFE34(0x1C0000, 0x5B0000, 0xC);
                g_ScriptVars[0] = 0x1C;
            }
            break;
        case 18:
            if (g_ScriptVars[0] == 0x1D) {
                Battle_StartScripted(0xC);
                g_SceneState.step_05 = 0x13;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x23) {
                SND_StopSequence(0, 0);
                SND_StopSequence(0, 1);
                Scene_SetupParty(6);
                g_SceneState.step_05 = 0x14;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x2B) {
                UI_SetMode(0xD);
                g_SceneState.step_05 = 0x15;
            }
            break;
        case 21:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 0x16;
            }
            break;
        case 22:
            SCENE_MESSAGE_WAIT(MSG_041, 0x17);
            break;
        case 23:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 0x18;
            SYS_SetFlag(g_SceneFlags, 0x36);
            Game_RequestAreaChange(0, 0x200000, 0x160000, 0x84);
            g_GamePrevSelection = 1;
            break;
        case 24:
            Area_StartScrollRoute(1);
            g_SceneState.step_05 = 0x19;
            break;
        case 25:
            if (g_ScriptVars[0] == 1) {
                UI_SetMode(0xD);
                g_SceneState.step_05 = 0x1A;
            }
            break;
        case 26:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 0x1B;
            }
            break;
        case 27:
            SCENE_MESSAGE_WAIT(MSG_056, 0x1C);
            break;
        case 28:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[2] = 6;
            D_80146871 ^= 1;
            g_SceneState.step_05 = 0x1D;
            Game_RequestAreaChange(5, 0x530000, 0x230000, 0x87);
            break;
        case 29:
            if (g_ScriptVars[0] == 6) {
                Char_RebuildPartyStats();
                D_80146258 ^= GAME_FLAG_SCROLL_LOCK;
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                Game_ClearScriptActive();
                SCENE_RETURN_TO_START();
            }
            break;
    }
}
