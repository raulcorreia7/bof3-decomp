#include "area167_13.h"

MATCH void func_801F4080(void) {
    Actor* work;

    work = g_SpadWork;
    if (work->z.part.integer != 0x3C0) {
        work->flags_00 &= 0xBF;
        SYS_ToggleFlag(g_SceneEventFlags, 0x4B);
    } else {
        g_ScriptState->cursor += 8;
    }
}
