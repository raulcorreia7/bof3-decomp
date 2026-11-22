#include "scena01_00.h"
#include "area/map.h"
#include "menu/panel.h"
#include "shared/etc.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FCEC0(void) {
    switch (g_ScenarioState.step) {
        case 0: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] == 0x64) {
                vars[0] = 0;
                UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                g_ScenarioState.step = 0x14;
            }
            if (vars[0] == 0x65) {
                vars[0]         = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                goto scene_return;
            }
            break;
        }
        case 0x14:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step = 0x15;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            break;
        case 0x15:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 0x16;
            break;
        case 0x16:
            if ((SND_XAIsIdle() & BYTE_MASK) == 0) {
                break;
            }
            g_ScenarioState.step = 0x17;
            break;
        case 0x17:
            if (g_Game.party_size == 2) {
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BEFORE_NUE, TO_COORD(0x50), TO_COORD(5), 0x88);
            } else if (g_Game.party_size == 3) {
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BEFORE_NUE, TO_COORD(0x51), TO_COORD(8), 0x89);
            } else {
                break;
            }
            g_ScriptVars[2]      = 8;
            g_ScenarioState.step = 0x18;
            SND_BGMPlay(7, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            break;
        case 0x18:
            if (g_ScriptVars[0] == 1) {
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                goto scene_return;
            }
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 0xC8) {
                D_8014865C           = -2;
                D_80148698           = 1;
                g_GameEntryState     = GAME_MODE_SHOP;
                g_MenuStep.step      = 0;
                D_80148699           = 0;
                g_ScenarioState.step = 3;
            } else if (g_ScriptVars[0] == 0xC9) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                goto scene_return;
            }
            break;
        case 3:
            if (g_GameStateIndex == 0) {
                SCRIPT_VARS_CLEAR_ALL();
                goto scene_return;
            }
            break;
        case 5: {
            u8* step;
            u8* vars;

            step = &g_ScenarioState.step;
            vars = g_ScriptVars;
            if (vars[0] == 0x64) {
                *step           = 1;
                vars[0]         = 0;
                g_ScriptVars[2] = 2;
                UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                *step = 0xA;
            }
            if (vars[0] == 0x65) {
                vars[0]         = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                goto scene_return;
            }
            break;
        }
        scene_return:
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 0xA:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step = 0xB;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            break;
        case 0xB:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 0xC;
            break;
        case 0xC:
            if ((SND_XAIsIdle() & BYTE_MASK) == 0) {
                break;
            }
            g_ScenarioState.step = 0xD;
            break;
        case 0xD:
            if (g_Game.party_size == 2) {
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BEFORE_NUE, TO_COORD(0x50), TO_COORD(5), 0x88);
            } else if (g_Game.party_size == 3) {
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BEFORE_NUE, TO_COORD(0x51), TO_COORD(8), 0x89);
            } else {
                break;
            }
            g_ScriptVars[2]      = 8;
            g_ScenarioState.step = 0x18;
            SND_BGMPlay(7, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            break;
    }
}
#else
INCLUDE_ASM(func_801FCEC0);
#endif
