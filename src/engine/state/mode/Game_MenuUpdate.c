#include "engine/game/00/game_00.h"

MATCH void Game_MenuUpdate(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameMenuSteps;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
