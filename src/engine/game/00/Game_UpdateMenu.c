#include "game_00.h"

MATCH void Game_UpdateMenu(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameMenuSteps;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
