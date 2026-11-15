#include "area013_13.h"

MATCH void func_801F2CEC(void) {
    Actor* work = g_Task;
    s32    diff = TO_COORD(28) + COORD_HALF - work->pos.x.fixed;

    work->direction_08    = diff >= 0 ? 3 : 7;
    g_ScriptState->unk_07 = abs(diff) / 0x8000;
    if (g_ScriptState->unk_07 != 0) {
        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    }
}
