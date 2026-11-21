#include "engine/game/00/game_00.h"

/* func_80197A60 */
MATCH void Game_BattleTurnToEncounter(void) {
    u16* state;

    Game_BattleQueueEncounterTurns();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    state = &g_GameEntrySubstate;
    (*state)++;
}
