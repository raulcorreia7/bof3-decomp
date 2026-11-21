#include "engine/game/00/game_00.h"

/* func_801AD44C */
MATCH void FieldAction_None(void) {
    Actor* work;

    work = (Actor*)GAME_WORK_AREA_PTR;
    work->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
}
