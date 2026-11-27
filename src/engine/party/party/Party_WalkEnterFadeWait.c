#include "engine/game/00/game_00.h"

/* func_801B8578 */
/* Waits for the fade-in to end, then advances the sub-step. */
MATCH void Party_WalkEnterFadeWait(void) {
    if (func_801C27E0(8) & BYTE_MASK) {
        SELF(Actor)->unk_03 = (SELF(Actor)->unk_03 + 1);
    }
}
