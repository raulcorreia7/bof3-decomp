#include "engine/game/00/game_00.h"

/* func_80197EFC */
MATCH void Game_ScrollToParty(void) {
    u16* state;

    Battle_ScrollToLeader();
    Battle_RunPartyAnims();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    state = &g_GameEntrySubstate;
    (*state)++;
}
