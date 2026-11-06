#include "area008_13.h"

MATCH void func_801F37BC(void) {
    Actor* s;
    Actor* e;
    u8     index;

    s     = g_Task;
    index = ((u8*)s)[0x0B];
    e     = &g_Actors[index];
    TASK_SET(e);
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->mode = 0x0E;
    } else if ((e->script_pc == 8) && (e->unk_4A == 1)) {
        Actor_SelectScript(4);
        s->mode = 0x0B;
    }
    g_Task = s;
}
