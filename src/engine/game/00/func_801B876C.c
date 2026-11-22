#include "game_00.h"

MATCH void func_801B876C(void) {
    TASK(Actor)->timer                             = 0;
    TASK(Actor)->param.unk_0B                      = TASK(Actor)->direction;
    g_Game.current->u.field.counter.unsigned_value = 4;
    TASK(Actor)->unk_03                            = 1;
}
