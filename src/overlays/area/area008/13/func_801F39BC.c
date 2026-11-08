#include "area008_13.h"

MATCH void func_801F39BC(void) {
    Actor* s;
    Actor* e;
    s32    index;

    s = (Actor*)&g_Actors[g_Task->param.unk_0B];
    s->header.flags |= ACTOR_FLAG_HIDDEN;
    s     = g_Task;
    index = s->param.unk_0B;
    e     = &g_Actors[index];
    TASK_SET(e);
    Actor_SelectScript(1);
    g_Task = s;
    Actor_Clear();
}
