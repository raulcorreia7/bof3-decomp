#include "engine/game/00/game_00.h"

/* func_801B7D00 */
/* Runs the down-ladder sub-step the actor's unk_04 selects. */
MATCH void Party_LadderDownRun(void) {
    g_PartyLadderDownSteps[TASK(Actor)->unk_04]();
}
