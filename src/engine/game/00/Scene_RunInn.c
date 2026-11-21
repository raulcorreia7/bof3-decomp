#include "game_00.h"

MATCH void Scene_RunInn(void) {
    u16 id;

    switch (g_SceneEventState.step) {
        case 0:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SceneEventState.step = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Char_RebuildPartyStats();
            SND_PauseBGM(g_SndBGMId);
            SND_StartXAStream(0, 1);
            g_SceneEventState.step = 2;
            break;
        case 2:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBGM(g_SndBGMId);
            UI_SetMode(1);
            g_AreaDrawFlags        = AREA_DRAW_ALL_FLAGS;
            g_SceneEventState.step = 3;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_SceneEventState.step = 10;
            break;
        case 5:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_SetScriptActive();
            g_SceneEventState.step = 6;
            break;
        case 6:
            D_8014865C             = -2;
            D_80148698             = 1;
            g_GameEntryState       = GAME_MODE_SHOP;
            g_MenuStep.step        = 0;
            D_80148699             = 0;
            g_SceneEventState.step = 7;
            break;
        case 7:
            if (g_GameEntryState != GAME_MODE_FIELD) {
                break;
            }
            g_SceneEventState.step = 10;
            break;
        case 10:
            id = g_SceneEventState.selection;
            if ((u8)id != GAME_NONE) {
                MESSAGE_START_WAIT(id);
            }
            g_SceneEventState.step = 11;
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneEventState.mode      = SCENE_EVENT_NONE;
            g_SceneEventState.step      = 0;
            g_SceneEventState.selection = 0;
            break;
        case 20:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SceneEventState.step = 21;
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Char_RebuildPartyStats();
            SND_PauseBGM(g_SndBGMId);
            SND_StartXAStream(0, 1);
            g_SceneEventState.step = 22;
            break;
        case 22:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBGM(g_SndBGMId);
            UI_SetMode(1);
            g_AreaDrawFlags        = AREA_DRAW_ALL_FLAGS;
            g_SceneEventState.step = 23;
            break;
        case 23:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_8014865C             = -2;
            D_80148698             = 1;
            g_GameEntryState       = GAME_MODE_SHOP;
            g_MenuStep.step        = 0;
            D_80148699             = 0;
            g_SceneEventState.step = 6;
            break;
    }
}
