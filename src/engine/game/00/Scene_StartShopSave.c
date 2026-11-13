#include "game_00.h"

MATCH void Scene_StartShopSave(void) {
    u16 id;

    switch (g_SceneEventStep) {
        case 0:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Char_RebuildPartyStats();
            SND_PauseBGM(g_SndBGMId);
            SND_StartXAStream(0, 1);
            g_SceneEventStep = 2;
            break;
        case 2:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBGM(g_SndBGMId);
            UI_SetMode(1);
            g_AreaDrawFlags  = AREA_DRAW_ALL_FLAGS;
            g_SceneEventStep = 3;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_SceneEventStep = 10;
            break;
        case 5:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_SetScriptActive();
            g_SceneEventStep = 6;
            break;
        case 6:
            D_8014865C       = -2;
            D_80148698       = 1;
            g_GameEntryState = GAME_STATE_SHOP;
            g_MenuStep.step  = 0;
            D_80148699       = 0;
            g_SceneEventStep = 7;
            break;
        case 7:
            if (g_GameEntryState != GAME_STATE_FIELD) {
                break;
            }
            g_SceneEventStep = 10;
            break;
        case 10:
            id = g_SceneEventSelection;
            if ((u8)id != GAME_NONE) {
                Message_StartAreaMessage(id);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
            }
            g_SceneEventStep = 11;
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneEventMode      = SCENE_EVENT_NONE;
            g_SceneEventStep      = 0;
            g_SceneEventSelection = 0;
            break;
        case 20:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SceneEventStep = 21;
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Char_RebuildPartyStats();
            SND_PauseBGM(g_SndBGMId);
            SND_StartXAStream(0, 1);
            g_SceneEventStep = 22;
            break;
        case 22:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBGM(g_SndBGMId);
            UI_SetMode(1);
            g_AreaDrawFlags  = AREA_DRAW_ALL_FLAGS;
            g_SceneEventStep = 23;
            break;
        case 23:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_8014865C       = -2;
            D_80148698       = 1;
            g_GameEntryState = GAME_STATE_SHOP;
            g_MenuStep.step  = 0;
            D_80148699       = 0;
            g_SceneEventStep = 6;
            break;
    }
}
