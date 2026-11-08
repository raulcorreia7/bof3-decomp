#include "game_00.h"

MATCH void Game_UpdateFishing(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameFishingSubstates;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
