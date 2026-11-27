#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB66C(void) {
    u8*  mode;
    u16* timer;

    switch (g_ScenarioState.step) {
        case 0:
            if ((g_UIWindowChannel & 2) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[0] = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA05_034, 1);
            } else {
                g_ScriptVars[0] = 0;
                SCENARIO_MESSAGE_WAIT(MSG_SCENA05_032, 2);
            }
            break;
        case 1:
            mode = &g_GameStateIndex;
            if (*mode == 2) {
                break;
            }
            UI_MessageStartArea(MSG_SCENA05_032);
            *mode                = 2;
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 3) {
                g_ScenarioState.step = 6;
            } else {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
        case 6:
            g_ScriptVars[0]      = 5;
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 8;
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
            SND_SeqStop(0, 0);
            SND_SEPlay(0x208);
            g_SndVoiceTargetVolume[16] = 0x7F;
            g_SndVoiceVolume[16]       = 0;
            g_ScenarioState.step       = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_ScenarioState.step = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_ScenarioState.step     = 11;
            g_ScenarioState.timer_06 = 0;
            break;
        case 11:
            timer = &g_ScenarioState.timer_06;
            (*timer)++;
            if (*timer >= 200) {
                SND_SEPlay(0x209);
                *timer               = 0;
                g_ScenarioState.step = 12;
            }
            SND_VoiceDecreaseTargetVolume(0x10, 4);
            SND_StartVolumeSweep(0x10);
            if ((s8)g_SndVoiceTargetVolume[16] < 9) {
                SND_SEPlay(0x209);
                *timer               = 0;
                g_ScenarioState.step = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_BGMPlay(0x4E, 0x64, 8);
            g_ScenarioState.step = 15;
            break;
        case 15:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_ScenarioState.step = 16;
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
            SND_SEPlay(0x208);
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 0x11) {
                break;
            }
            g_ScenarioState.step = 22;
            SYS_SetFlag(g_SceneFlags, 0x2A);
            Game_RequestAreaChange(0x51, TO_COORD(90), TO_COORD(6), 0x84);
            g_GamePrevSelection = 0xFF;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            g_ScenarioState.step = 24;
            g_ScriptVars[2]      = 2;
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
            SND_SEPlay(0x209);
            Game_BattleStartScripted(0x15);
            g_ScenarioState.step = 25;
            break;
        case 25:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x3C);
            g_ScenarioState.step = 26;
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
            g_ScenarioState.step = 27;
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
            g_ScenarioState.step = 28;
            Game_RequestAreaChange(0x4E, TO_COORD(40), TO_COORD(173), 0x88);
            g_GamePrevSelection = 0x4F;
            break;
        case 28:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_ScrollStartRoute(0);
            g_ScenarioState.step = 29;
            SYS_SetFlag(g_SceneFlags, 0x2C);
            break;
        case 29:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_ScenarioState.step = 30;
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
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
    }
}
