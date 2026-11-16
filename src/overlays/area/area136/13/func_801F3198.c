#include "area136_13.h"

MATCH void func_801F3198(void) {
    u8* state;

    switch (g_SceneEventState.step) {
        case 0:
            if (Item_VitalHas(VITAL_ITEM_ID_CARD)) {
                g_SceneEventState.step = 10;
            } else {
                g_SceneEventState.step = 1;
            }
            break;
        case 1:
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(0x83);
                *state                 = GAME_REQUEST_MESSAGE;
                g_SceneEventState.step = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneEventState.mode      = 0;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
                Game_ClearScriptActive();
            }
            break;
        case 10:
            SYS_SetFlag(g_SceneFlags, 0x2E);
            FAKE_BARRIER(); /* FAKE: sets the state address after the flag call. */
            state = &g_GameStateIndex;
            if (*state != GAME_REQUEST_MESSAGE) {
                Message_StartAreaMessage(0x82);
                *state = GAME_REQUEST_MESSAGE;
                SYS_ToggleFlag(g_SceneEventFlags, 0x29);
                g_SceneEventState.step = 0xB;
            }
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801BE1B0(0);
                g_SceneEventState.step = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[3] == 0x28) {
                if (g_SceneEventState.selection == 0) {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(51), TO_COORD(71), AREA_ENTRY_MAP_LOADING | FACING_UP);
                } else {
                    Game_RequestAreaChange(AREA_ID_BLACK_SHIP_BOOST_COUNTER, TO_COORD(8), TO_COORD(34), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                }
                g_SceneEventState.step = 0xD;
            }
            break;
        case 13:
            if (g_ScriptVars[3] == 0) {
                Game_ClearScriptActive();
                g_SceneEventState.mode      = 0;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
                SYS_ClearFlag(g_SceneFlags, 0x2E);
            }
            break;
    }
}
