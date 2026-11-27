#include "engine/game/00/game_00.h"

/* func_801B8A0C */
/* Returns the actor to mode 1, facing its stored walk direction. */
MATCH void Party_CellWalkEnd(void) {
    Actor* work;

    g_Game.current->u.field.counter.value = 3;
    work                                  = SELF(Actor);
    work->direction                       = work->param.unk_0B;
    Script_Request(SELF(Actor)->direction);
    g_Game.current->u.field.mode.value = 0;
    SELF(Actor)->header.mode           = 1;
    SELF(Actor)->header.step           = 0;
    SELF(Actor)->unk_03                = 0;
}
