#include "engine/game/00/game_00.h"

/* func_801B69C0 */
/* Runs the handler of the actor's current step in mode 2. */
MATCH void Party_RunMoveStep(void) {
    g_PartyMoveSteps[SELF(Actor)->header.step]();
}
