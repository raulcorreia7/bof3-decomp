#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FABA8(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0;
                UI_ModeSet(0);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.timer_06 = 60;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step     = 2;
            }
            break;
        case 2:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                func_8019FA28(0x63, TO_COORD(6), TO_COORD(38), 0x80);
                g_ScenarioState.step = 3;
                g_ScenarioState.flags_01 |= 1;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 10) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 4:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE && g_UIMessageRequest == 0xC) {
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[1]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                g_GameFlags &= 0xFEFF;
            }
            break;
        case 6:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags = 0x1F;
                g_ScriptVars[0] = 1;
                UI_ModeSet(1);
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 5) {
                UI_ModeSet(0);
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (g_SysThreads[2].state == 0) {
                g_ScenarioState.timer_06 = 60;
                g_AreaDrawFlags          = 0;
                g_ScenarioState.step     = 9;
            }
            break;
        case 9:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                SND_BGMFadeOut(g_SndBGMId, 100, 8);
                SND_XAStartStream(0, 1);
                func_801C16B8();
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if ((u8)SND_XAIsIdle() != 0) {
                g_AreaDrawFlags = 0x1F;
                g_ScenarioState.flags_01 &= 0xFE;
                Area_BundleRunOpcodes();
                UI_ModeSet(1);
                g_ScenarioState.step = 11;
            }
            break;
        case 11:
            if (g_SysThreads[2].state == 0) {
                g_ScriptVars[0]      = 6;
                g_ScenarioState.step = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 8) {
                g_GameFlags |= 0x80;
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 13:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE && g_UIMessageRequest == 0x11) {
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                g_GameFlags &= 0xFEFF;
            }
            break;
        case 15:
            func_801BE1B0(2);
            g_ScenarioState.step = 16;
            break;
        case 16:
            if (g_ScriptVars[0] == 1) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 17;
            }
            break;
        case 17:
            func_8019FA28(0x63, TO_COORD_HALF(6), TO_COORD(35), 0x83);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_ScenarioState.step = 18;
            break;
        case 18:
            g_AreaDrawFlags          = 0x1F;
            g_ScenarioState.timer_06 = 60;
            g_ScenarioState.step     = 19;
            break;
        case 19:
            if (g_ScenarioState.timer_06 != 0) {
                if (g_ScenarioState.timer_06 == 50) {
                    SND_SEPlay(0x201);
                }
                if (g_ScenarioState.timer_06 == 10) {
                    SND_SEPlay(0x201);
                }
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 20;
            }
            break;
        case 20:
            g_AreaScrollTargetX = TO_COORD_HALF(5);
            g_AreaScrollTargetY = TO_COORD_HALF(11);
            Area_InitMapRenderer();
            g_ScenarioState.timer_06 = 10;
            g_ScenarioState.step     = 21;
            break;
        case 21:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 22;
                g_ScriptVars[0]++;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 4) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 23;
            }
            break;
        case 23:
            g_AreaScrollTargetX = TO_COORD_HALF(6);
            g_AreaScrollTargetY = TO_COORD(35);
            Area_InitMapRenderer();
            g_ScenarioState.timer_06 = 10;
            g_ScenarioState.step     = 24;
            break;
        case 24:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 25;
                g_ScriptVars[0]++;
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 9) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 26;
            }
            break;
        case 26:
            g_AreaScrollTargetX = TO_COORD(6);
            g_AreaScrollTargetY = TO_COORD(9);
            Area_InitMapRenderer();
            g_ScenarioState.step = 27;
            break;
        case 27:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 28;
                g_ScriptVars[0]++;
            }
            break;
        case 28:
            if (g_ScriptVars[0] == 0xD) {
                Game_ClearScriptActive();
                g_GameCellType = 3;
                SYS_SetFlag(g_SceneFlags, 0x1C);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
