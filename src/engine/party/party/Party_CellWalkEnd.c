#include "engine/game/00/game_00.h"

/* func_801B8A0C */
/* Returns the actor to mode 1, facing its stored walk direction. */
MATCH void Party_CellWalkEnd(void) {
    Actor* work;

    g_Game.current->u.field.counter.value = 3;
    work                                  = TASK(Actor);
    work->direction                       = work->param.unk_0B;
    Script_Request(TASK(Actor)->direction);
    g_Game.current->u.field.mode.value = 0;
    TASK(Actor)->header.mode           = 1;
    TASK(Actor)->header.step           = 0;
    TASK(Actor)->unk_03                = 0;
}
