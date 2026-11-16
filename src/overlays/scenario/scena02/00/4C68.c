#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB868(void) {
    switch (g_SceneState.step_05) {
        case 0:
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0B));
            g_SceneState.step_05 = 1;
            break;
        case 1: {
            u8* counter;

            counter = &D_80146867;
            if (*counter == 0x4B) {
                func_801C601C(2);
                func_801BE1B0(0xF);
                g_SceneState.step_05 = 2;
            }
            (*counter)++;
            break;
        }
        case 2:
            if (g_ScriptVars[0] == 0x27 && g_AreaCameraMoving == 0) {
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            g_ScriptVars[0] = 0x37;
            switch (g_PartyFieldOrder[0]) {
                case 0:
                    func_801BE1B0(0x10);
                    break;
                case 3:
                    func_801BE1B0(0x1A);
                    break;
                case 4:
                    func_801BE1B0(0x19);
                    break;
            }
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x39) {
                func_801FCD14(0x92);
                g_SceneState.step_05 = 7;
                g_ScriptVars[0]      = 0x3A;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x3C) {
                SYS_SetFlag(g_SceneFlags, 0x2F);
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 15:
            Message_StartAreaMessage(0x7F);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 20:
            func_801FCECC(0x99);
            SND_StopSequence(0, 0);
            g_ScriptVars[0] = 0x41;
            func_801BE1B0(0x11);
            func_801C601C(3);
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] == 0x47) {
                func_801BFE34(TO_COORD(64), TO_COORD_HALF(39), 0xF);
                func_801C7A54(0xF);
                g_SceneState.step_05 = 0x18;
            }
            break;
        case 24:
            if (g_ScriptVars[0] == 0x4B) {
                SYS_SetFlag(g_SceneFlags, 0x30);
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 25:
            switch (g_Game.members[0].facing) {
                case 0:
                    func_801BE1B0(0x16);
                    g_SceneState.step_05 = 0x1A;
                    break;
                case 1:
                    func_801BE1B0(0x14);
                    g_SceneState.step_05 = 0x1A;
                    break;
                case 2:
                    func_801BE1B0(0x17);
                    g_SceneState.step_05 = 0x1A;
                    break;
                case 3:
                    func_801BE1B0(0x13);
                    g_SceneState.step_05 = 0x1A;
                    break;
                case 7:
                    func_801BE1B0(0x15);
                    g_SceneState.step_05 = 0x1A;
                    break;
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 0x51) {
                SYS_SetFlag(g_SceneFlags, 0x32);
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 30: {
            u8* counter;

            counter = &D_80146867;
            if (++*counter >= 0x10) {
                *counter              = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        }
    }
}
