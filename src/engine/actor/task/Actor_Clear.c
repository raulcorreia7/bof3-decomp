#include "engine/game/00/game_00.h"

MATCH void Actor_Clear(void) {
    TASK(Actor)->header.flags = 0;
    TASK(Actor)->header.mode  = 0;
    ACTOR_CLEAR_STEP();
    TASK(Actor)->unk_03 = 0;
    TASK(Actor)->unk_04 = 0;
}
