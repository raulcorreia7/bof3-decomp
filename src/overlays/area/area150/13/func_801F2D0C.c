#include "area150_13.h"

MATCH void func_801F2D0C(void) {
    switch (g_SceneEventStep) {
        case 10:
            Message_StartAreaMessage(0x2D);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 11;
            break;
        case 12:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                Game_RequestAreaChange(0xBD, TO_COORD(0x1780), TO_COORD(0xF00), 0xA);
                D_8014504B       = 0xA;
                D_80144F57       = 0xF0;
                D_80144F54       = 0;
                D_80144F56       = 0;
                D_80146880       = 0;
                D_80146881       = 0;
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SceneState.flags_01 |= 1;
            }
            break;
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                if (SYS_TestFlag(D_80144EF8, 3)) {
                    Message_StartAreaMessage(0x25);
                } else {
                    Message_StartAreaMessage(0x20);
                }
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                g_SceneEventStep = 21;
            }
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C16B8();
                SND_StartXAStream(0, 1);
                g_SceneEventStep = 22;
            }
            break;
        case 22:
            if (SND_IsXAIdle() & BYTE_MASK) {
                g_ScriptVars[0] = 1;
                SND_StartBGM(0x95, 100, 0x10);
                UI_SetMode(UI_MODE_FADE_IN);
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                SYS_ClearFlag(D_80144EF8, 3);
                SYS_ClearFlag(D_80144EF8 + 0x30, 0x8A);
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
    }
}
