#include "scena01_00.h"
#include "area/map.h"
#include "menu/panel.h"
#include "shared/etc.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

MATCH void func_801FCEC0(void) {
    s32 party_size;

    switch (g_ScenarioState.step) {
        case 0: {
            u8* vars = g_ScriptVars;

            if (vars[0] == 0x64) {
                vars[0] = 0;
                UI_ModeSet(0xD);
                g_ScenarioState.step = 0x14;
            }
            if (vars[0] == 0x65) {
                vars[0] = 0;
                goto reset_vars;
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
            if ((SND_XAIsIdle() & BYTE_MASK) != 0) {
                g_ScenarioState.step = 0x17;
            }
            break;
        case 0x17:
            party_size = g_PartySize;
            if (party_size == 2) {
                g_ScriptVars[2]      = 8;
                g_ScenarioState.step = 0x18;
                Game_RequestAreaChange(0xA, 0x500000, 0x50000, 0x88);
                SND_BGMPlay(7, 0x64, 8);
            } else {
                goto check_party_size_three;
            }
            break;
        case 0x18:
            if (g_ScriptVars[0] == 1) {
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0xC8) {
                    D_8014865C           = -2;
                    D_80148698           = 1;
                    g_GameEntryState     = GAME_MODE_SHOP;
                    g_MenuStep.step      = 0;
                    D_80148699           = 0;
                    g_ScenarioState.step = 3;
                } else if (g_ScriptVars[0] == 0xC9) {
                    g_ScriptVars[0] = 0;
                    goto reset_vars;
                }
            }
            break;
        case 3:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0] = 0;
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x64) {
                g_ScenarioState.step = 1;
                g_ScriptVars[0]      = 0;
                g_ScriptVars[2]      = 2;
                UI_ModeSet(0xD);
                g_ScenarioState.step = 0xA;
            }
            if (g_ScriptVars[0] == 0x65) {
                g_ScriptVars[0] = 0;
                goto reset_vars;
            }
            break;
        reset_vars:
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
        clear_script:
            Game_ClearScriptActive();
        step_zero:
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step = 0xB;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            break;
        case 11:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 0xC;
            break;
        case 12:
            if ((SND_XAIsIdle() & BYTE_MASK) != 0) {
                g_ScenarioState.step = 0xD;
            }
            break;
        case 13:
            party_size = g_PartySize;
            if (party_size == 2) {
                goto party_size_two;
            }
        check_party_size_three:
            if (party_size == 3) {
                goto party_size_three;
            }
            break;
        party_size_two:
            g_ScriptVars[2]      = 8;
            g_ScenarioState.step = 0x18;
            Game_RequestAreaChange(0xA, 0x500000, 0x50000, 0x88);
            SND_BGMPlay(7, 0x64, 8);
            break;
        party_size_three:
            g_ScriptVars[2]      = 8;
            g_ScenarioState.step = 0x18;
            Game_RequestAreaChange(0xA, 0x510000, 0x80000, 0x89);
            SND_BGMPlay(7, 0x64, 8);
            break;
    }
}
