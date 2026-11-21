#include "engine/game/00/game_00.h"

MATCH void Game_UpdateBattle(void) {
    Callback* handlers;
    u16       state;

    handlers = (Callback*)g_GameBattleSteps;
    state    = g_GameEntrySubstate;
    handlers[state]();
}
