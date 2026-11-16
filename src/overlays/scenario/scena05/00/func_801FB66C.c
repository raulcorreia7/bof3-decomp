#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB66C(void) {
    u8*  mode;
    u16* timer;

    switch (g_SceneState.step_05) {
        case 0:
            if ((g_UiWindowChannel & 2) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[0] = 0;
                Message_StartAreaMessage(0x22);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 1;
            } else {
                g_ScriptVars[0] = 0;
                Message_StartAreaMessage(0x20);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 2;
            }
            break;
        case 1:
            mode = &g_GameStateIndex;
            if (*mode == 2) {
                break;
            }
            Message_StartAreaMessage(0x20);
            *mode                = 2;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 3) {
                g_SceneState.step_05 = 6;
            } else {
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
        case 6:
            g_ScriptVars[0]      = 5;
            g_SceneState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_SceneState.step_05 = 8;
            SYS_SetFlag(g_SceneFlags, 0x28);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x81);
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x80);
                    break;
            }
            break;
        case 8:
            SND_StopSequence(0, 0);
            SND_PlayCue(0x208);
            g_SndVoiceTargetVolume[16] = 0x7F;
            g_SndVoiceVolume[16]       = 0;
            g_SceneState.step_05       = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_SceneState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_SceneState.step_05 = 11;
            D_80146876           = 0;
            break;
        case 11:
            timer = &D_80146876;
            (*timer)++;
            if (*timer >= 200) {
                SND_PlayCue(0x209);
                *timer               = 0;
                g_SceneState.step_05 = 12;
            }
            func_8015D104(0x10, 4);
            SND_StartVolumeSweep(0x10);
            if ((s8)g_SndVoiceTargetVolume[16] < 9) {
                SND_PlayCue(0x209);
                *timer               = 0;
                g_SceneState.step_05 = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_PlayBGM(0x4E, 0x64, 8);
            g_SceneState.step_05 = 15;
            break;
        case 15:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_SceneState.step_05 = 16;
            SYS_SetFlag(g_SceneFlags, 0x29);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x83);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x82);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 16:
            SND_PlayCue(0x208);
            g_SceneState.step_05 = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 0x11) {
                break;
            }
            g_SceneState.step_05 = 22;
            SYS_SetFlag(g_SceneFlags, 0x2A);
            Game_RequestAreaChange(0x51, TO_COORD(90), TO_COORD(6), 0x84);
            g_GamePrevSelection = 0xFF;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            g_SceneState.step_05 = 24;
            D_80146866           = 2;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(197), TO_COORD(14), 0x86);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(197), TO_COORD(14), 0x85);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 24:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_PlayCue(0x209);
            Battle_StartScripted(0x15);
            g_SceneState.step_05 = 25;
            break;
        case 25:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x3C);
            g_SceneState.step_05 = 26;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Scene_SetupParty(8);
                    break;
                case 2:
                    Scene_SetupParty(7);
                    break;
            }
            break;
        case 26:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_SceneState.step_05 = 27;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(9), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                    g_GamePrevSelection = 0x4E;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(9), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP);
                    g_GamePrevSelection = 0x4E;
                    break;
            }
            break;
        case 27:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            g_SceneState.step_05 = 28;
            Game_RequestAreaChange(0x4E, TO_COORD(40), TO_COORD(173), 0x88);
            g_GamePrevSelection = 0x4F;
            break;
        case 28:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 29;
            SYS_SetFlag(g_SceneFlags, 0x2C);
            break;
        case 29:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_SceneState.step_05 = 30;
            SYS_SetFlag(g_SceneFlags, 0x2B);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(7), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_RIGHT);
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(7), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
                    break;
            }
            break;
        case 30:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
