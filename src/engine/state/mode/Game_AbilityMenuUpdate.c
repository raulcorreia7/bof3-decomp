#include "engine/game/00/game_00.h"

MATCH void Game_AbilityMenuUpdate(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_MenuAbilityOpen;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
