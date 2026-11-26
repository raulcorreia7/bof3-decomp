#include "engine/game/00/game_00.h"

/* func_801B876C */
/* Stores the actor's facing as its walk direction and sets the run speed index. */
MATCH void Party_CellWalkStart(void) {
    SELF(Actor)->timer                             = 0;
    SELF(Actor)->param.unk_0B                      = SELF(Actor)->direction;
    g_Game.current->u.field.counter.unsigned_value = 4;
    SELF(Actor)->unk_03                            = 1;
}
