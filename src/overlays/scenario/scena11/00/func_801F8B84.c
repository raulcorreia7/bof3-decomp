#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8B84(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScriptVars[0] = 1;
            Scene_SetupParty(1);
            g_ScenarioState.step_05 = 1;
            break;
        case 1: {
            u8* mode;

            if (g_ScriptVars[0] != 7) {
                break;
            }
            mode = &g_GameStateIndex;
            if (*mode == 2) {
                break;
            }
            *mode           = 8;
            g_AreaDrawFlags = 0;
            break;
        }
        case 5:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScenarioState.step_05 = 6;
            g_ScriptVars[0]         = 0;
            SYS_SetFlag(g_SceneFlags, 0xA);
            Game_RequestAreaChange(0x82, 0x290000, 0x540000, 0x82);
            break;
        case 6:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            Game_SetScriptActive();
            if (g_GameStateIndex == 2) {
                break;
            }
            UI_SetMode(0xD);
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            g_ScenarioState.step_05 = 0xB;
            break;
        case 11:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_GameStateIndex = 8;
            g_AreaDrawFlags  = 0;
            SND_PlaySequence(0, 1, 0x64, 0x64);
            break;
        case 12:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScenarioState.step_05 = 0xD;
            g_ScriptVars[0]         = 0;
            Game_RequestAreaChange(0x82, 0x290000, 0x540000, 0x82);
            break;
        case 13:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 0xE;
            break;
        case 14:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 20:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0xA);
            if (g_ScriptVars[3] == 1) {
                g_ScenarioState.step_05 = 0x1E;
                Game_RequestAreaChange(0x82, 0x290000, 0x540000, 0x83);
                g_GamePrevSelection = 0xFF;
            } else {
                g_ScenarioState.step_05 = 0x28;
                Game_RequestAreaChange(0x82, 0x290000, 0x540000, 0x84);
            }
            break;
        case 30:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SND_StartXAStream(7, 1);
            g_ScenarioState.step_05 = 0x20;
            break;
        case 32:
            if ((SND_IsXAIdle() & 0xFF) == 0) {
                break;
            }
            g_ScenarioState.step_05 = 0x21;
            break;
        case 33:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_StartXAStream(6, 1);
            g_ScenarioState.step_05 = 0x22;
            break;
        case 34:
            if ((SND_IsXAIdle() & 0xFF) == 0) {
                break;
            }
            g_ScriptVars[0]         = 5;
            g_ScenarioState.step_05 = 0x23;
            break;
        case 35:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            Char_LoseHP(0xFFFF, 7);
            Game_ClearScriptActive();
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 40:
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 0x29;
            break;
        case 41:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            SND_PlaySequence(0, 1, 0x64, 0x64);
            g_ScenarioState.step_05 = 0x2A;
            break;
        case 42: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 0xA) {
                break;
            }
            SND_FadeOutSequence(0, 1, 4, 0x1E);
            *progress               = 0;
            g_ScenarioState.step_05 = 0x2B;
            UI_SetMode(0xD);
            break;
        }
        case 43:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 0x2C;
            break;
        case 44:
            Message_StartAreaMessage(MSG_064);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 0x2D;
            break;
        case 45:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step_05 = 0x2E;
            g_ScriptVars[2]         = 1;
            SYS_SetFlag(g_SceneFlags, 0xB);
            Game_RequestAreaChange(0x82, 0x290000, 0x530000, 0x85);
            SND_PlayBGM(0x83, 0x64, 8);
            break;
        case 46:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_PauseBGM(0x83);
            SND_StartXAStream(2, 1);
            g_ScenarioState.step_05 = 0x2F;
            break;
        case 47:
            if ((SND_IsXAIdle() & 0xFF) == 0) {
                break;
            }
            SND_ResumeBGM(0x83);
            g_ScenarioState.step_05 = 0x30;
            break;
        case 48:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0xC);
            Game_ClearScriptActive();
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}
