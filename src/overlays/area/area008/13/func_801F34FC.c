#include "area008_13.h"

MATCH void func_801F34FC(void) {
    Actor* s;
    Actor* e;
    u8     index;

    s     = g_Task;
    index = s->unk_0B;
    e     = &g_Actors[index];
    TASK_SET(e);
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->header.mode = 0x0E;
    } else if ((e->script_pc == 2) && (e->unk_4A == 1)) {
        s->header.mode = 5;
    }
    g_Task = s;
}
