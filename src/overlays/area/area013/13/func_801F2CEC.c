#include "area013_13.h"

MATCH void func_801F2CEC(void) {
    Actor* work = SELF(Actor);
    s32    diff = TO_COORD(28) + COORD_HALF - work->pos.x.fixed;

    work->direction      = diff >= 0 ? 3 : 7;
    g_ScriptState->steps = abs(diff) / 0x8000;
    if (g_ScriptState->steps != 0) {
        Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
    }
}
