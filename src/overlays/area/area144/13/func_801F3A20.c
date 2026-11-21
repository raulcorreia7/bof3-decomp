#include "area144_13.h"

MATCH void func_801F3A20(void) {
    s32 diff;

    diff = (TO_COORD(29) + COORD_HALF - g_Task->pos.y.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->steps = abs(diff);
        if (diff < 0) {
            g_Task->direction = FACING_UP;
        } else {
            g_Task->direction = FACING_DOWN;
        }
        Area_MoveActorRoute(g_ScriptState, g_Task->direction);
    }
}
