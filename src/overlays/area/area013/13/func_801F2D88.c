#include "area013_13.h"

MATCH void func_801F2D88(void) {
    Actor* work = SELF(Actor);

    work->direction      = FACING_UP;
    g_ScriptState->steps = abs(TO_COORD(2) - work->pos.y.fixed) / 0x8000;
    if (g_ScriptState->steps != 0) {
        Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
    }
}
