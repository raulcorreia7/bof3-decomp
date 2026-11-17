#include "game_00.h"

/* func_801AD69C */
MATCH void FieldAction_NoneAlt(void) {
    Actor* work;

    work = (Actor*)GAME_WORK_AREA_PTR;
    work->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
}
