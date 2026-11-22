#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB36C(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA02_101, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            switch (g_PartyFieldOrder[0]) {
                case 0:
                    Scene_SetupParty(0xC);
                    break;
                case 3:
                    Scene_SetupParty(0x1C);
                    break;
                case 4:
                    Scene_SetupParty(0x1B);
                    break;
            }
            g_ScenarioState.step_05 = 2;
            break;
        case 2: {
            u8* vars;

            vars = g_ScriptVars;
            switch (vars[0]) {
                case 8:
                    if ((u8)Party_SpendZenny(0x32, 0) != 0) {
                        vars[0]         = 9;
                        g_ScriptVars[1] = 0;
                        g_ScriptVars[2] = 0;
                        g_ScriptVars[3] = 0;
                        Game_ClearScriptActive();
                        SCENARIO_RETURN_TO_START();
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                    } else {
                        SCENARIO_MESSAGE_WAIT(MSG_SCENA02_109, 3);
                    }
                    break;
                case 0xF:
                    SCENARIO_MESSAGE_WAIT(MSG_SCENA02_108, 4);
                    break;
            }
            break;
        }
        case 10:
            g_ScriptVars[0]         = 1;
            g_ScenarioState.step_05 = 0xC;
            break;
        case 12: {
            u8* vars;

            vars = g_ScriptVars;
            switch (vars[0]) {
                case 8:
                    if ((u8)Party_SpendZenny(0x32, 0) != 0) {
                        vars[0]         = 9;
                        g_ScriptVars[1] = 0;
                        g_ScriptVars[2] = 0;
                        g_ScriptVars[3] = 0;
                        Game_ClearScriptActive();
                        SCENARIO_RETURN_TO_START();
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                    } else {
                        SCENARIO_MESSAGE_WAIT(MSG_SCENA02_109, 0xD);
                    }
                    break;
                case 0xF:
                    SCENARIO_MESSAGE_WAIT(MSG_SCENA02_108, 4);
                    break;
            }
            break;
        }
        case 3:
        case 4:
        case 13:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 0x10;
            g_ScriptVars[1] = 1;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            SCENARIO_RETURN_TO_START();
            break;
        case 20: {
            u8* state;
            u8* vars;

            state = &g_GameStateIndex;
            if (*state == GAME_REQUEST_MESSAGE) {
                break;
            }
            vars = g_ScriptVars;
            switch (vars[0]) {
                case 8:
                    if ((u8)Party_SpendZenny(0x32, 0) != 0) {
                        vars[0]         = 9;
                        g_ScriptVars[1] = 0;
                        g_ScriptVars[2] = 0;
                        g_ScriptVars[3] = 0;
                        Game_ClearScriptActive();
                        SCENARIO_RETURN_TO_START();
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                    } else {
                        UI_MessageStartArea(MSG_SCENA02_109);
                        *state                  = GAME_REQUEST_MESSAGE;
                        g_ScenarioState.step_05 = 0xD;
                    }
                    break;
                case 0xF:
                    UI_MessageStartArea(MSG_SCENA02_108);
                    *state                  = GAME_REQUEST_MESSAGE;
                    g_ScenarioState.step_05 = 4;
                    break;
            }
            break;
        }
    }
}
