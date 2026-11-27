#include "engine/game/00/game_00.h"

/* func_801B73B0 */
/* Runs the jump sub-step the actor's unk_03 selects. */
MATCH void Party_JumpRun(void) {
    g_PartyJumpSteps[SELF(Actor)->unk_03]();
}
