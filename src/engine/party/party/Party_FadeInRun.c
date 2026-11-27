#include "engine/game/00/game_00.h"

/* func_801B726C */
/* Runs the fade-in sub-step the actor's unk_03 selects. */
MATCH void Party_FadeInRun(void) {
    g_PartyFadeInSteps[SELF(Actor)->unk_03]();
}
