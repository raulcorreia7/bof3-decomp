#include "area135_14.h"

MATCH void func_801F5020(void) {
    Actor* work;
    u8     count;

    g_ScriptState->cursor -= 2;
    work         = g_SpadWork;
    count        = work->unk_0A;
    work->unk_0A = count + 0xFF;
    if (count == 0) {
        g_SpadWork->flags_00 = 0;
        g_SpadWork->unk_04 = 0;
    } else {
        g_SpadWork->unk_09 = g_SpadWork->unk_0A;
        func_8019F818(work);
        g_SpadWork->unk_09 = 0;
    }
}
