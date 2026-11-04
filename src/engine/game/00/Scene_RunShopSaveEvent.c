#include "game_00.h"

MATCH void Scene_RunShopSaveEvent(void) {
    u16 id;

    switch (D_801448EC) {
        case 0:
            Game_SetScriptActive();
            UI_SetMode(0);
            D_801448EC = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            SND_PauseBgm(g_SndBgmId);
            SND_StartXaStream(0, 1);
            D_801448EC = 2;
            break;
        case 2:
            if ((SND_IsXaIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBgm(g_SndBgmId);
            UI_SetMode(1);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            D_801448EC      = 3;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_801448EC = 10;
            break;
        case 5:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_SetScriptActive();
            D_801448EC = 6;
            break;
        case 6:
            D_8014865C       = -2;
            D_80148698       = 1;
            g_GameEntryState = 7;
            D_80148650       = 0;
            D_80148699       = 0;
            D_801448EC       = 7;
            break;
        case 7:
            if (g_GameEntryState != 2) {
                break;
            }
            D_801448EC = 10;
            break;
        case 10:
            id = D_801448ED;
            if ((u8)id != GAME_NONE) {
                Message_StartAreaMessage(id);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
            }
            D_801448EC = 11;
            break;
        case 11:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            D_801448EB = 0;
            D_801448EC = 0;
            D_801448ED = 0;
            break;
        case 20:
            Game_SetScriptActive();
            UI_SetMode(0);
            D_801448EC = 21;
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            SND_PauseBgm(g_SndBgmId);
            SND_StartXaStream(0, 1);
            D_801448EC = 22;
            break;
        case 22:
            if ((SND_IsXaIdle() & BYTE_MASK) == 0) {
                break;
            }
            SND_ResumeBgm(g_SndBgmId);
            UI_SetMode(1);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            D_801448EC      = 23;
            break;
        case 23:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_8014865C       = -2;
            D_80148698       = 1;
            g_GameEntryState = 7;
            D_80148650       = 0;
            D_80148699       = 0;
            D_801448EC       = 6;
            break;
    }
}
