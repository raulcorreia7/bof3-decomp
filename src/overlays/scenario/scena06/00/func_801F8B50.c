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
                g_AreaScrollTargetX  = TO_COORD(53);
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
                SYS_SetFlag(g_SceneFlags, 13);
                Game_RequestAreaChange(AREA_ID_RHAPALA_DOCK, TO_COORD(51), TO_COORD(33), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0xD) {
                SYS_SetFlag(g_SceneFlags, 15);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
        case 10:
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 11;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(2);
                g_SceneState.step_05 = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x15) {
                SYS_SetFlag(g_SceneFlags, 14);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
        case 20:
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 21;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(0);
                g_SceneState.step_05 = 22;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 1) {
                SYS_SetFlag(g_SceneFlags, 16);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
        case 30:
            Message_StartAreaMessage(0x13);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 31;
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
