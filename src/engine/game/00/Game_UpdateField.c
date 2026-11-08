#include "game_00.h"

MATCH void Game_UpdateField(void) {
    u32* counter;

    Game_UpdateScenario();
    Area_RunFrame();

    switch (g_GameStateIndex) {
        case GAME_REQUEST_IDLE:
            break;
        case GAME_REQUEST_MENU:
            UI_SetMode(2);
            func_80198BC4(0);
            g_GameEntryState    = GAME_STATE_MENU;
            g_GameEntrySubstate = 0;
            break;
        case GAME_REQUEST_MESSAGE:
            g_GameEntryState = GAME_STATE_MESSAGE;
            break;
        case GAME_REQUEST_BATTLE:
            g_Battle.phase.mode     = BATTLE_MODE_ENTRANCE;
            g_Battle.phase.step     = 0;
            g_Battle.phase.sub_step = 0;
            D_80145E9B              = 0;
            D_80145FDB              = 0;
            D_8014611B              = 0;
            counter                 = &g_BattleCount;
            g_GameEntryState        = GAME_STATE_BATTLE;
            g_GameEntrySubstate     = 0;
            (*counter)++;
            break;
        case GAME_REQUEST_CAMERA_LOOK:
            g_GameEntryState = GAME_STATE_CAMERA_LOOK;
            break;
        case GAME_REQUEST_AREA_CHANGE: {
            u8 selection;

            g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
            selection = g_SndBGMId;
            if (selection != GAME_NONE && g_GamePrevSelection != selection) {
                SND_StartDecrescendo(g_SelectionCues[selection * 4], D_80181EBB[selection * 4], 100, 16);
            }
            if (g_GameEntryMode != GAME_NONE) {
                UI_SetMode(g_GameEntryMode);
                func_80198BC4(0);
            }
            selection = g_SndBGMId;
            if (selection != GAME_NONE && g_GamePrevSelection != selection) {
                SND_StopSequence(g_SelectionCues[selection * 4], D_80181EBB[selection * 4]);
            }
            g_GameEntryState = GAME_STATE_AREA_LOAD;
            break;
        }
        case GAME_REQUEST_SHOP:
            g_MenuStep.step     = 6;
            D_8014865C          = -1;
            g_MenuStep.sub_step = 0;
            g_MenuStep.state    = 0;
            g_GameEntryState    = GAME_STATE_SHOP;
            g_GameEntrySubstate = 0;
            break;
        case GAME_REQUEST_ABILITY_MENU:
            g_GameEntryState    = GAME_STATE_ABILITY_MENU;
            g_GameEntrySubstate = 0;
            g_MenuStep.step     = 0;
            g_MenuStep.sub_step = 0;
            g_MenuStep.state    = 0;
            break;
        case GAME_REQUEST_STATUS_MENU:
            g_GameEntryState    = GAME_STATE_STATUS_MENU;
            g_GameEntrySubstate = 0;
            g_MenuStep.step     = 0;
            g_MenuStep.sub_step = 0;
            g_MenuStep.state    = 0;
            break;
        case GAME_REQUEST_SCENE_CAMERA:
            D_8014626C       = 1;
            D_8014626D       = 0;
            D_8014626E       = 0;
            D_8014626F       = 0;
            D_80146270       = 0;
            g_GameEntryState = GAME_STATE_SCENE_CAMERA;
            break;
    }
}
