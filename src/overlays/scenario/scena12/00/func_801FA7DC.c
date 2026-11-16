#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Word 1 of the overlay's secondary-state handler run: the step sequence of primary state 7. */
MATCH void func_801FA7DC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(0xBC, 0x158000, 0xB0000, 0x8F);
            g_GamePrevSelection = 0xFF;
            return;
        case 1:
            if (g_ScriptVars[0] != 2) {
                return;
            }
            g_GameFlags |= 0x80;
            SYS_SetFlag(g_SceneFlags, 0x2A);
            g_ScriptVars[2] = 7;
            Game_ClearScriptActive();
            break;
        case 5:
            Message_StartAreaMessage(MSG_011);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 6;
            return;
        case 6:
            if (g_GameStateIndex == 2) {
                return;
            }
            Game_ClearScriptActive();
            g_ScriptVars[2] = 7;
            break;
        case 10:
            Game_SetScriptActive();
            g_GameFlags |= 8;
            Scene_SetupParty(0x10);
            g_SceneState.step_05 = 0xB;
            return;
        case 11: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                return;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 8;
            g_SceneState.step_05 = 0xC;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0xA0000, 0x570000, 0x91);
            return;
        }
        case 12: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 4) {
                return;
            }
            *progress            = 5;
            g_SceneState.step_05 = 0xD;
            SND_PlayCue(0x20E);
            SND_PlayBGM(0x8F, 0x64, 8);
            return;
        }
        case 13: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 0x14) {
                return;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 0;
            g_SceneState.step_05 = 0xE;
            SYS_SetFlag(g_SceneFlags, 0x2B);
            g_GamePrevSelection = 0xFF;
            Game_RequestAreaChange(0xBC, 0x120000, 0x70000, 0x92);
            g_GamePrevSelection = 0x8F;
            return;
        }
        case 14:
            Area_StartScrollRoute(4);
            g_SceneState.step_05 = 0xF;
            return;
        case 15: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                return;
            }
            *progress            = 0;
            g_SceneState.step_05 = 0x10;
            g_ScriptVars[2]      = 0;
            g_GamePrevSelection  = 0xFF;
            Game_RequestAreaChange(0xBC, 0xC0000, 0x590000, 0x93);
            g_GamePrevSelection = 0x8F;
            return;
        }
        case 16:
            if (g_ScriptVars[0] != 5) {
                return;
            }
            UI_SetMode(0xD);
            g_SceneState.step_05 = 0x11;
            return;
        case 17:
            if (g_UiWindowEffectBusy != 0) {
                return;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 0x12;
            return;
        case 18:
            Message_StartAreaMessage(MSG_023);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0x13;
            return;
        case 19: {
            u8* armed = &g_GameStateIndex;
            if (*armed == 2) {
                return;
            }
            *armed               = 6;
            g_SceneState.step_05 = 0x14;
            return;
        }
        case 20:
            if (g_GameStateIndex != 0) {
                return;
            }
            g_SceneState.step_05 = 0x1D;
            g_GameFlags ^= 0x80;
            SND_StopSequence(0, 0);
            SND_StopSequence(0, 1);
            SYS_SetFlag(g_SceneFlags, 0x2C);
            Char_RebuildPartyStats();
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 7:
                    SYS_SetFlag(g_SceneFlags, 0x32);
                    break;
                case 8:
                    SYS_SetFlag(g_SceneFlags, 0x33);
                    break;
                case 9:
                    SYS_SetFlag(g_SceneFlags, 0x34);
                    break;
                case 10:
                    SYS_SetFlag(g_SceneFlags, 0x35);
                    break;
                case 13:
                    SYS_SetFlag(g_SceneFlags, 0x36);
                    break;
                case 14:
                    SYS_SetFlag(g_SceneFlags, 0x37);
                    break;
                case 15:
                    SYS_SetFlag(g_SceneFlags, 0x38);
                    break;
                case 16:
                    SYS_SetFlag(g_SceneFlags, 0x39);
                    break;
                case 17:
                    SYS_SetFlag(g_SceneFlags, 0x3A);
                    break;
                case 18:
                    SYS_SetFlag(g_SceneFlags, 0x3B);
                    break;
            }
            g_ScriptVars[2] = 9;
            Game_RequestAreaChange(0xBC, 0x370000, 0x3F8000, 0x94);
            g_GamePrevSelection = 0x8B;
            return;
        case 29:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 0x1E;
            return;
        case 30: {
            u8* progress = &g_ScriptVars[0];
            if (*progress != 1) {
                return;
            }
            Area_SetCellCode(0x38, 0x47, 0xC0);
            Area_SetCellCode(0x38, 0x48, 0xC0);
            Area_SetCellCode(0x39, 0x47, 0xA1);
            Area_SetCellCode(0x39, 0x48, 0xA1);
            Area_SetCellCode(0x37, 0x3F, 0xC0);
            Area_SetCellCode(0x37, 0x40, 0xC0);
            Area_SetCellCode(0x1F, 0x15, 0xA1);
            Area_SetCellCode(0x1F, 0x16, 0xA1);
            Area_SetCellCode(0x1C, 3, 0xC0);
            Area_SetCellCode(0x1D, 3, 0xC0);
            g_GameFlags ^= 0x28;
            Game_ClearScriptActive();
            *progress       = 0;
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            break;
        }
        default:
            return;
    }
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 0;
}
