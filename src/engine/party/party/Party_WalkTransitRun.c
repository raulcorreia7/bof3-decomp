#include "engine/game/00/game_00.h"

/* func_801B8234 */
/* Runs the walk transit sub-step the actor's unk_03 selects. */
MATCH void Party_WalkTransitRun(void) {
    g_Game.current->u.field.mode.unsigned_value = 2;
    g_PartyWalkTransitSteps[TASK(Actor)->unk_03]();
}
