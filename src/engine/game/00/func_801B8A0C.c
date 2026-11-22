#include "game_00.h"

MATCH void func_801B8A0C(void) {
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
