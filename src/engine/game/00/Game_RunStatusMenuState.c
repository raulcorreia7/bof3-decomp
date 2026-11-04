#include "game_00.h"

MATCH void Game_RunStatusMenuState(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_MenuStatusOpen;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
