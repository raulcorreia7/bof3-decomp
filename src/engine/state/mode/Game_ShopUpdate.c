#include "engine/game/00/game_00.h"

MATCH void Game_ShopUpdate(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameShopSteps;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
