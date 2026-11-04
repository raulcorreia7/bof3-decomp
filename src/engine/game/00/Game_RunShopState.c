#include "game_00.h"

MATCH void Game_RunShopState(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameStateHandlers;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
