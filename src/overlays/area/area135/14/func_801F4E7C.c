#include "area135_14.h"

MATCH void func_801F4E7C(void) {
    Actor* work;

    work = g_Task;
    if (work->x.fixed == 0x168000 && work->y.fixed == 0x128000) {
        g_ScriptState->cursor = (u16)(g_ScriptState->cursor + 1);
    }
    g_Task->unk_04 = 0;
}
