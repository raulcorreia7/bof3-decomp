#include "engine/game/00/game_00.h"

/* func_801B7344 */
/* Waits for the fade-in to end, then returns the actor to mode 1. */
MATCH void Party_FadeInWait(void) {
    if (func_801C27E0(8) & BYTE_MASK) {
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
    }
}
