#include "game_00.h"

MATCH void func_801ABEE0(void) {
    TASK(Actor)->active_flags &= 0xDF;
    if (Actor_GetOwner() == 1) {
        ACTOR_CLEAR_STEP();
    }
}
