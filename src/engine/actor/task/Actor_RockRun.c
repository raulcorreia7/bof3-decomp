#include "engine/game/00/game_00.h"

/* func_8019B364 */
/* Runs the mode of the current type 0x17 rock actor. */
MATCH void Actor_RockRun(void) {
    g_ActorRockModes[SELF(Actor)->header.mode]();
}
