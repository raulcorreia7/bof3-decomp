#include "game_00.h"

MATCH void func_8019F9D0(void) {
    SELF(Actor)->header.mode = SELF(Actor)->param.unk_0B;
    ACTOR_CLEAR_STEP();
    SELF(Actor)->unk_03 = 0;
    SELF(Actor)->unk_04 = 0;
    SELF(Actor)->timer  = 0;
}
