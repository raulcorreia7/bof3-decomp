#include "game_00.h"

MATCH void func_8019F9D0(void) {
    TASK(Actor)->header.mode = TASK(Actor)->param.unk_0B;
    ACTOR_CLEAR_STEP();
    TASK(Actor)->unk_03 = 0;
    TASK(Actor)->unk_04 = 0;
    TASK(Actor)->timer  = 0;
}
