#include "game_00.h"

MATCH void func_801AD44C(void) {
    Actor* work;

    work = (Actor*)GAME_WORK_AREA_PTR;
    work->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
}
