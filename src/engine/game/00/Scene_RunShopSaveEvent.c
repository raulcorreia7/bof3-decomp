#include "game_00.h"

MATCH void Scene_RunShopSaveEvent(void) {
    u16 id;

    switch (g_SaveData.scene_event.step) {
        case 0:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SaveData.scene_event.step = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            SND_PauseBgm(g_SaveData.snd_bgm_id);
            SND_StartXAStream(0, 1);
            g_SaveData.scene_event.step = 2;
            break;
        case 2:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBgm(g_SaveData.snd_bgm_id);
            UI_SetMode(1);
            g_AreaDrawFlags             = AREA_DRAW_ALL_FLAGS;
            g_SaveData.scene_event.step = 3;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_SaveData.scene_event.step = 10;
            break;
        case 5:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_SetScriptActive();
            g_SaveData.scene_event.step = 6;
            break;
        case 6:
            D_8014865C                  = -2;
            D_80148698                  = 1;
            g_GameEntryState            = 7;
            D_80148650                  = 0;
            D_80148699                  = 0;
            g_SaveData.scene_event.step = 7;
            break;
        case 7:
            if (g_GameEntryState != 2) {
                break;
            }
            g_SaveData.scene_event.step = 10;
            break;
        case 10:
            id = g_SaveData.scene_event.selection;
            if ((u8)id != GAME_NONE) {
                Message_StartAreaMessage(id);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
            }
            g_SaveData.scene_event.step = 11;
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            g_SaveData.scene_event.mode      = 0;
            g_SaveData.scene_event.step      = 0;
            g_SaveData.scene_event.selection = 0;
            break;
        case 20:
            Game_SetScriptActive();
            UI_SetMode(0);
            g_SaveData.scene_event.step = 21;
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            SND_PauseBgm(g_SaveData.snd_bgm_id);
            SND_StartXAStream(0, 1);
            g_SaveData.scene_event.step = 22;
            break;
        case 22:
            if ((SND_IsXAIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBgm(g_SaveData.snd_bgm_id);
            UI_SetMode(1);
            g_AreaDrawFlags             = AREA_DRAW_ALL_FLAGS;
            g_SaveData.scene_event.step = 23;
            break;
        case 23:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_8014865C                  = -2;
            D_80148698                  = 1;
            g_GameEntryState            = 7;
            D_80148650                  = 0;
            D_80148699                  = 0;
            g_SaveData.scene_event.step = 6;
            break;
    }
}
