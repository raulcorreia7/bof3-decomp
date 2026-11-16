#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB36C(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Message_StartAreaMessage(0x65);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            switch (g_PartyFieldOrder[0]) {
                case 0:
                    func_801BE1B0(0xC);
                    break;
                case 3:
                    func_801BE1B0(0x1C);
                    break;
                case 4:
                    func_801BE1B0(0x1B);
                    break;
            }
            g_SceneState.step_05 = 2;
            break;
        case 2: {
            u8* vars;

            vars = g_ScriptVars;
            switch (vars[0]) {
                case 8:
                    if ((u8)Party_SpendZenny(0x32, 0) != 0) {
                        vars[0]    = 9;
                        D_80146865 = 0;
                        D_80146866 = 0;
                        D_80146867 = 0;
                        Game_ClearScriptActive();
                        g_SceneState.step_05  = 0;
                        g_SceneState.state_04 = 0;
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                    } else {
                        Message_StartAreaMessage(0x6D);
                        g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                        g_SceneState.step_05 = 3;
                    }
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                    g_SceneState.step_05 = 4;
                    break;
            }
            break;
        }
        case 10:
            g_ScriptVars[0]      = 1;
            g_SceneState.step_05 = 0xC;
            break;
        case 12: {
            u8* vars;

            vars = g_ScriptVars;
            switch (vars[0]) {
                case 8:
                    if ((u8)Party_SpendZenny(0x32, 0) != 0) {
                        vars[0]    = 9;
                        D_80146865 = 0;
                        D_80146866 = 0;
                        D_80146867 = 0;
                        Game_ClearScriptActive();
                        g_SceneState.step_05  = 0;
                        g_SceneState.state_04 = 0;
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                    } else {
                        Message_StartAreaMessage(0x6D);
                        g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                        g_SceneState.step_05 = 0xD;
                    }
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                    g_SceneState.step_05 = 4;
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
            D_80146865      = 1;
            D_80146866      = 0;
            D_80146867      = 0;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
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
                        vars[0]    = 9;
                        D_80146865 = 0;
                        D_80146866 = 0;
                        D_80146867 = 0;
                        Game_ClearScriptActive();
                        g_SceneState.step_05  = 0;
                        g_SceneState.state_04 = 0;
                        SYS_SetFlag(g_SceneFlags, 0x24);
                        SYS_SetFlag(g_SceneFlags, 0x25);
                        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                    } else {
                        Message_StartAreaMessage(0x6D);
                        *state               = GAME_REQUEST_MESSAGE;
                        g_SceneState.step_05 = 0xD;
                    }
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    *state               = GAME_REQUEST_MESSAGE;
                    g_SceneState.step_05 = 4;
                    break;
            }
            break;
        }
    }
}
