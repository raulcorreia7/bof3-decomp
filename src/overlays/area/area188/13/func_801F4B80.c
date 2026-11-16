#include "area188_13.h"

MATCH void func_801F4B80(void) {
    u8* state;

    switch (g_SceneEventState.step) {
        case 0:
            if ((Item_VitalHas(VITAL_ITEM_ID_CARD) & BYTE_MASK) != 0) {
                g_SceneEventState.step = 0xA;
            } else {
                g_SceneEventState.step = 1;
            }
            break;
        case 1:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(MSG_131);
                *state                 = GAME_REQUEST_MESSAGE;
                g_SceneEventState.step = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
                Game_ClearScriptActive();
            }
            break;
        case 10:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(MSG_130);
                *state = GAME_REQUEST_MESSAGE;
                SYS_ToggleFlag(g_SceneEventFlags, 0x69);
                g_SceneEventState.step = 0xB;
            }
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SetupParty(6);
                g_SceneEventState.step = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[3] == 0x28) {
                if (g_SceneEventState.selection == 0) {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP, TO_COORD(51), TO_COORD(71), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                } else {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP, TO_COORD(8), TO_COORD(34), AREA_ENTRY_MAP_LOADING | 8);
                }
                g_SceneEventState.step = 0xD;
            }
            break;
        case 13:
            if (g_ScriptVars[3] == 0) {
                Game_ClearScriptActive();
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
            }
            break;
    }
}
