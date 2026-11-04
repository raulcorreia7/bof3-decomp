#include "game_00.h"

MATCH void Game_RunMenuState(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameEntryHandlers;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
