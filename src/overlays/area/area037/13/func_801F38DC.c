#include "area037_13.h"

MATCH void func_801F38DC(void) {
    s8* state;
    u8* request;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(state + 0x63C, 114);
                Game_RequestAreaChange(AREA_ID_WYNDIA_LOWER, TO_COORD_HALF(44), TO_COORD(39), FACING_UP);
                g_GameRequestType = 0xFE;
                *state            = *state + 1;
            }
            break;
        case 1:
            request = &g_GameStateIndex;
            if (*request == GAME_REQUEST_IDLE) {
                Message_StartAreaMessage(MSG_AREA037_GAME_READY);
                *request = GAME_REQUEST_MESSAGE;
                *state   = *state + 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(1);
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                *state          = *state + 1;
            }
            break;
        case 3:
            if (WINDOW_EFFECT_IDLE()) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                *state                 = 0;
                g_ScriptVars[3]        = 0;
            }
            break;
    }
}
