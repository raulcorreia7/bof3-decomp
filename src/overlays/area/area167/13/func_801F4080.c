#include "area167_13.h"

MATCH void func_801F4080(void) {
    Actor* work;

    work = g_Task;
    if (COORD_INT(work->pos.z) != 0x3C0) {
        work->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SYS_ToggleFlag(g_SaveData.scene_event_flags, 0x4B);
    } else {
        g_ScriptState->cursor += 8;
    }
}
