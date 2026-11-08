#include "game_00.h"

MATCH void Game_UpdateBattle(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameBattleSubstates;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
