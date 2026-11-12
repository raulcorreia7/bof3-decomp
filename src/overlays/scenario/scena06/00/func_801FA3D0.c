#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA3D0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_SceneState.step_05 = 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_SceneState.step_05 = 3;
            }
            break;
        case 1:
        case 3:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_SceneState.step_05 = 5;
            SYS_SetFlag(g_SceneFlags, 0x1D);
            g_ScriptVars[2] = 4;
            g_SceneState.flags_01 |= 1;
            func_8019FA28(0x5C, 0x180000, 0x3D0000, 0x89);
            g_GamePrevSelection = 0x3C;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            Battle_StartScripted(0x1B);
            g_SceneState.step_05 = 6;
            break;
        case 7:
            func_801BE1B0(0xE);
            g_SceneState.step_05 = 0xA;
            SYS_SetFlag(g_SceneFlags, 0x1F);
            func_8019FA28(0x5C, 0x180000, 0x3C0000, 0x8A);
            g_GamePrevSelection = 0xFF;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            func_801C16B8();
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 6;
            g_SceneState.flags_01 ^= 1;
            func_8019FA28(0x57, 0x310000, 0x2D0000, 4);
            break;
        case 15:
            func_801BE1B0(0xB);
            g_SceneState.step_05 = 0x10;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            UI_SetMode(0xD);
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_SceneState.step_05 = 0x11;
            break;
        case 17:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x2B);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x12;
            break;
        case 18:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C16B8();
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 6;
                SYS_ClearFlag(g_SceneFlags, 0x1D);
                g_SceneState.flags_01 ^= 1;
                func_8019FA28(0x57, 0x310000, 0x2D0000, 4);
            }
            break;
        case 20:
            func_801BE1B0(0xD);
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(0xD);
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_SceneState.step_05 = 0x16;
            break;
        case 22:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x17;
            break;
        case 23:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C16B8();
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 6;
                SYS_ClearFlag(g_SceneFlags, 0x1D);
                g_SceneState.flags_01 ^= 1;
                func_8019FA28(0x57, 0x310000, 0x2D0000, 4);
            }
            break;
    }
}
