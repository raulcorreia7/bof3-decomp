#include "area135_14.h"

MATCH void func_801F5020(void) {
    Actor* work;
    u8     count;

    g_ScriptState->cursor -= 2;
    work         = g_Task;
    count        = work->unk_0A;
    work->unk_0A = count + 0xFF;
    if (count == 0) {
        g_Task->header.flags = 0;
        g_Task->unk_04       = 0;
    } else {
        g_Task->unk_09 = g_Task->unk_0A;
        func_8019F818(work);
        g_Task->unk_09 = 0;
    }
}
