#include "area085_13.h"

MATCH void func_801F3AF8(void) {
    SELF(Actor)->active_flags &= 0xFE;
    Area_SceneSelectRecord(0x184);
    Script_Select(0);
    SELF(Actor)->mirror = 1;
    SELF(Actor)->header.flags |= ACTOR_FLAG_STEP_MOVE;
}
