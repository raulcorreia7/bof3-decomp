#include "area128_13.h"

MATCH void func_801F30BC(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                func_801BE1B0(6);
                SYS_SetFlag(state + 0x63C, 0x88);
                goto done;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(state + 0x63C, 0x89);
                Game_RequestAreaChange(0x79, TO_COORD(0x2A), TO_COORD(0x1A), 7);
            done:
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
