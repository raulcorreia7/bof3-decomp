#include "area013_13.h"

MATCH void func_801F2D88(void) {
    Actor* work = g_Task;

    work->direction_08    = FACING_UP;
    g_ScriptState->unk_07 = abs(TO_COORD(2) - work->pos.y.fixed) / 0x8000;
    if (g_ScriptState->unk_07 != 0) {
        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    }
}
