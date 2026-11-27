#include "engine/game/00/game_00.h"

/* func_801B9048 */
/* Runs the fall sub-step the actor's unk_03 selects. */
MATCH void Party_FallThroughRun(void) {
    g_Game.current->u.field.mode.unsigned_value = 6;
    g_PartyFallThroughSteps[SELF(Actor)->unk_03]();
}
