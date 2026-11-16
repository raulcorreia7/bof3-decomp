#include "game_00.h"

MATCH void Game_UpdateShisuMenu(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_MenuShisuOpen;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
