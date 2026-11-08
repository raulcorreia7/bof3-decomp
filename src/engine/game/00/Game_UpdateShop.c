#include "game_00.h"

MATCH void Game_UpdateShop(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameShopSubstates;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
