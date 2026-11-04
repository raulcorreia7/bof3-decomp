#include "game_00.h"

MATCH void Message_RunAreaMessage(void) {
    s8* state;

    state = &D_801448EC;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage(0xD8);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = (u8)*state + 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                D_801448EB = 0;
                *state     = 0;
                D_801448ED = 0;
            }
            return;
    }
}
