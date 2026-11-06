#include "area135_14.h"

MATCH void func_801F4E7C(void) {
    Actor* work;

    work = g_Task;
    if (work->pos.x.fixed == 0x168000 && work->pos.y.fixed == 0x128000) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 1);
    }
    g_Task->unk_04 = 0;
}
