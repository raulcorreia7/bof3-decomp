#include "area135_14.h"

MATCH void func_801F5020(void) {
    Actor* work;
    u8     count;

    g_ScriptState->cursor -= 2;
    work         = SELF(Actor);
    count        = work->unk_0A;
    work->unk_0A = count + 0xFF;
    if (count == 0) {
        SELF(Actor)->header.flags = 0;
        SELF(Actor)->unk_04       = 0;
    } else {
        SELF(Actor)->timer = SELF(Actor)->unk_0A;
        Actor_ShatterRun(work);
        SELF(Actor)->timer = 0;
    }
}
