#include "area167_13.h"

MATCH void func_801F4080(void) {
    Actor* work;

    work = g_Task;
    if (COORD_INT(work->pos.z) != 960) {
        work->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SYS_ToggleFlag(g_SceneEventFlags, 75);
    } else {
        g_ScriptState->cursor += 8;
    }
}
