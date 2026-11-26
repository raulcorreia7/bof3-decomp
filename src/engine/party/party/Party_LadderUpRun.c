#include "engine/game/00/game_00.h"

/* func_801B790C */
/* Runs the up-ladder sub-step the actor's unk_04 selects. */
MATCH void Party_LadderUpRun(void) {
    Callback handler = g_PartyLadderUpSteps[SELF(Actor)->unk_04];
    handler();
}
