#include "engine/game/00/game_00.h"

/* func_801B81EC */
/* Waits for the fade-in to end, then advances the ladder sub-step. */
MATCH void Party_LadderWaitFadeIn(void) {
    if (func_801C27E0(8) & BYTE_MASK) {
        TASK(Actor)->unk_04++;
    }
}
