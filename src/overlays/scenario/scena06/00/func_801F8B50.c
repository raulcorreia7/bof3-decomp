#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8B50(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Message_StartAreaMessage(0xD);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(0);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                g_AreaScrollTargetX  = 0x350000;
                g_AreaCameraStep     = 0x20;
                g_SceneState.step_05 = 3;
                g_AreaScrollTargetY  = g_Game.members[0].pos.y.fixed;
            }
            break;
        case 3:
            if (g_AreaCameraMoving == 0) {
                g_ScriptVars[0]      = 2;
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0xA) {
                UI_SetMode(0xD);
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x1A);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 7;
                SYS_SetFlag(g_SceneFlags, 0xD);
                Game_RequestAreaChange(0x5E, 0x330000, 0x210000, 0x81);
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0xD) {
                SYS_SetFlag(g_SceneFlags, 0xF);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 10:
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(2);
                g_SceneState.step_05 = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x15) {
                SYS_SetFlag(g_SceneFlags, 0xE);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 20:
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(0);
                g_SceneState.step_05 = 0x16;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 1) {
                SYS_SetFlag(g_SceneFlags, 0x10);
                Game_ClearScriptActive();
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 30:
            Message_StartAreaMessage(0x13);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x1F;
            break;
        case 31:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
