#include "engine/game/00/game_00.h"

/* func_8019CB94 */
/* Runs the mode of the current block actor. */
MATCH void Actor_BlockRun(void) {
    g_ActorBlockModes[TASK(Actor)->header.mode]();
}
