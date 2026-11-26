#include "engine/game/00/game_00.h"

/* Actor_BlockRun */
/* Runs the mode of the current type 0x30 block actor. */
/* func_8019CB94 */
MATCH void Actor_BlockRun(void) {
    g_ActorBlockModes[TASK(Actor)->header.mode]();
}
