#include "game_00.h"

MATCH void Game_RunAbilityMenuState(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_MenuAbilityOpen;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
