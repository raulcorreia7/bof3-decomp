#include "commu00_00.h"

/* FAKE: holds the state cell address in a local pointer so it stays in a
 * callee-saved register across the request call, as the original does. */
MATCH void func_801F1B30(void) {
    u8* state;

    state = &g_GameStateIndex;
    if (*state == GAME_REQUEST_IDLE) {
        Message_StartAreaMessage(MSG_151);
        *state           = GAME_REQUEST_MESSAGE;
        FAIRY_EVENT_STEP = FAIRY_EVENT_STEP - 1;
    }
}
