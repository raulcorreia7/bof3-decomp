#include "game_00.h"

MATCH void func_80198B00(void) {
    Area_DispatchScene();
    func_80199308();
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        g_GameEntryState = GAME_STATE_FIELD;
    }
}
