#include "game_00.h"

MATCH void func_801979D4(void) {
    if ((g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
        D_80146256       = 0x10u;
        g_GameStateIndex = GAME_REQUEST_IDLE;
        g_GameEntryState = GAME_STATE_FIELD;
    }

    func_80199230();
}
