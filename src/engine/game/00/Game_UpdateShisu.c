#include "game_00.h"

MATCH void Game_UpdateShisu(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameShisuSteps;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
