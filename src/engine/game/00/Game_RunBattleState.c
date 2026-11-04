#include "game_00.h"

MATCH void Game_RunBattleState(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameModeHandlers;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
