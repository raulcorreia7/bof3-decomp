#include "area188_13.h"

MATCH void func_801F4B80(void) {
    u8* state;

    switch (g_SceneEventStep) {
        case 0:
            if ((Item_VitalHas(VITAL_ITEM_ID_CARD) & BYTE_MASK) != 0) {
                g_SceneEventStep = 0xA;
            } else {
                g_SceneEventStep = 1;
            }
            break;
        case 1:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(0x83);
                *state           = GAME_REQUEST_MESSAGE;
                g_SceneEventStep = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneEventMode      = SCENE_EVENT_NONE;
                g_SceneEventStep      = 0;
                g_SceneEventSelection = 0;
                Game_ClearScriptActive();
            }
            break;
        case 10:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(0x82);
                *state = GAME_REQUEST_MESSAGE;
                SYS_ToggleFlag(g_SceneEventFlags, 0x69);
                g_SceneEventStep = 0xB;
            }
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(6);
                g_SceneEventStep = 0xC;
            }
            break;
        case 12:
            if (D_80146867 == 0x28) {
                if (g_SceneEventSelection == 0) {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP, TO_COORD(51), TO_COORD(71), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                } else {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP, TO_COORD(8), TO_COORD(34), AREA_ENTRY_MAP_LOADING | 8);
                }
                g_SceneEventStep = 0xD;
            }
            break;
        case 13:
            if (D_80146867 == 0) {
                Game_ClearScriptActive();
                g_SceneEventMode      = SCENE_EVENT_NONE;
                g_SceneEventStep      = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
