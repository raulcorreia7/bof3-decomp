#include "area013_13.h"

MATCH void func_801F2D88(void) {
    Actor* work = g_Task;

    work->direction_08    = 1;
    g_ScriptState->unk_07 = abs(0x20000 - work->pos.y.fixed) / 0x8000;
    if (g_ScriptState->unk_07 != 0) {
        func_801ABBA8(g_ScriptState, g_Task->direction_08);
    }
}
