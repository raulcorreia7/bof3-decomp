#include "area198_13.h"

MATCH void func_801F3528(void) {
    s32 diff;

    diff = (TO_COORD(25) - g_Task->pos.x.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->unk_07 = abs(diff);
        g_Task->direction_08  = FACING_RIGHT;
        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    }
}
