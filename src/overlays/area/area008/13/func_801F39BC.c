#include "area008_13.h"

MATCH void func_801F39BC(void) {
    Actor* s;
    Actor* e;
    s32    idx;

    s = (Actor*)&g_Actors[((u8*)g_Task)[0x0B]];
    s->flags |= ACTOR_FLAG_HIDDEN;
    s   = g_Task;
    idx = ((u8*)s)[0x0B];
    e   = &g_Actors[idx];
    TASK_SET(e);
    Actor_SelectScript(1);
    g_Task = s;
    Actor_Clear();
}
