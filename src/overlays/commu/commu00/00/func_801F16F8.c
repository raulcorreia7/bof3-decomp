#include "commu00_00.h"

/* FAKE: holds the state cell address in a local pointer so it stays in a
 * callee-saved register across the request call, as the original does. */
MATCH void func_801F16F8(void) {
    u8* state;
    s8* variant;

    state = &g_GameStateIndex;
    if (*state != GAME_REQUEST_MESSAGE) {
        if (g_UIMessageRequest == 0xF9) {
            variant = &g_SceneEventState.step;
            *variant += 1;
        } else {
            UI_MessageStartArea(MSG_AREA175_ASK_HELP_TOPIC);
            *state = GAME_REQUEST_MESSAGE;
        }
    }
}
