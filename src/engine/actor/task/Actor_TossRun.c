#include "engine/game/00/game_00.h"

/* func_8019ADA4 */
/* Runs the toss mode of the current type 0x32 actor. */
MATCH void Actor_TossRun(void) {
    g_ActorTossModes[SELF(Actor)->header.mode]();
}
