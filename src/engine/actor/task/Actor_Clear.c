#include "engine/game/00/game_00.h"

MATCH void Actor_Clear(void) {
    SELF(Actor)->header.flags = 0;
    SELF(Actor)->header.mode  = 0;
    ACTOR_CLEAR_STEP();
    SELF(Actor)->unk_03 = 0;
    SELF(Actor)->unk_04 = 0;
}
