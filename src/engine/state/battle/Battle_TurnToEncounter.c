#include "engine/game/00/game_00.h"

/* func_80197A60 */
MATCH void Battle_TurnToEncounter(void) {
    u16* state;

    Battle_QueueEncounterTurns();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    state = &g_GameEntrySubstate;
    (*state)++;
}
