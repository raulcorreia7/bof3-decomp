#include "area135_14.h"

MATCH void func_801F5020(void) {
    Actor* work;
    u8     count;

    g_ScriptState->cursor -= 2;
    work         = TASK(Actor);
    count        = work->unk_0A;
    work->unk_0A = count + 0xFF;
    if (count == 0) {
        TASK(Actor)->header.flags = 0;
        TASK(Actor)->unk_04       = 0;
    } else {
        TASK(Actor)->timer = TASK(Actor)->unk_0A;
        Actor_ShatterRun(work);
        TASK(Actor)->timer = 0;
    }
}
