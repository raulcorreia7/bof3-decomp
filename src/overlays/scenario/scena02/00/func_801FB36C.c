#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB36C(void) {
    u8 paid;
    u8 mode;
    u8 step;

    mode = g_SceneState.step_05;
    switch (mode) {
        case 0:
            Message_StartAreaMessage(0x65);
            g_GameStateIndex = 2;
            step             = 1;
            break;

        case 1:
            if (g_GameStateIndex == 2) {
                return;
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
                default:
                    break;
            }
            step = 2;
            break;

        case 2:
            switch (g_ScriptVars[0]) {
                case 8:
                    paid = Party_SpendZenny(0x32, 0);
                    if (paid != 0) {
                        g_ScriptVars[0] = 9;
                        goto spent;
                    }
                    Message_StartAreaMessage(0x6D);
                    g_GameStateIndex = 2;
                    step             = 3;
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    g_GameStateIndex = 2;
                    step             = 4;
                    break;
                default:
                    return;
            }
            break;

        case 3:
        case 4:
        case 13:
            if (g_GameStateIndex == 2) {
                return;
            }
            g_ScriptVars[0] = 0x10;
            D_80146865      = 1;
            D_80146866      = 0;
            D_80146867      = 0;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            return;

        case 10:
            g_ScriptVars[0] = 1;
            step            = 12;
            break;

        case 12:
            switch (g_ScriptVars[0]) {
                case 8:
                    paid = Party_SpendZenny(0x32, 0);
                    if (paid != 0) {
                        g_ScriptVars[0] = 9;
                        goto spent;
                    }
                    Message_StartAreaMessage(0x6D);
                    g_GameStateIndex = 2;
                    step             = 13;
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    g_GameStateIndex = 2;
                    step             = 4;
                    break;
                default:
                    return;
            }
            break;

        case 20:
            if (g_GameStateIndex == 2) {
                return;
            }
            switch (g_ScriptVars[0]) {
                case 8:
                    paid = Party_SpendZenny(0x32, 0);
                    if (paid != 0) {
                        g_ScriptVars[0] = 9;
                        goto spent;
                    }
                    Message_StartAreaMessage(0x6D);
                    g_GameStateIndex = 2;
                    step             = 13;
                    break;
                case 0xF:
                    Message_StartAreaMessage(0x6C);
                    g_GameStateIndex = 2;
                    step             = 4;
                    break;
                default:
                    return;
            }
            break;
    }
    g_SceneState.step_05 = step;
    return;

spent:
    D_80146865 = 0;
    D_80146866 = 0;
    D_80146867 = 0;
    Game_ClearScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 0;
    SYS_SetFlag(g_SceneFlags, 0x24);
    SYS_SetFlag(g_SceneFlags, 0x25);
    SND_PlayCue(0x106);
}
#else
INCLUDE_ASM(func_801FB36C);
#endif
