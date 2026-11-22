#include "area144_13.h"

MATCH void func_801F3A20(void) {
    s32 diff;

    diff = (TO_COORD(29) + COORD_HALF - TASK(Actor)->pos.y.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->steps = abs(diff);
        if (diff < 0) {
            TASK(Actor)->direction = FACING_UP;
        } else {
            TASK(Actor)->direction = FACING_DOWN;
        }
        Area_MoveActorRoute(g_ScriptState, TASK(Actor)->direction);
    }
}
