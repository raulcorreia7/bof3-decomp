#include "area135_14.h"

MATCH void func_801F4E7C(void) {
    Actor* work;

    work = g_Task;
    if (work->pos.x.fixed == TO_COORD(22) + COORD_HALF && work->pos.y.fixed == TO_COORD(18) + COORD_HALF) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 1);
    }
    g_Task->unk_04 = 0;
}
