#include "area008_13.h"

MATCH void func_801F39BC(void) {
    Actor* s;
    Actor* e;
    s32    index;

    s = (Actor*)&g_Actors[TASK_BYTES[0x0B]];
    s->flags |= ACTOR_FLAG_HIDDEN;
    s     = g_Task;
    index = ((u8*)s)[0x0B];
    e     = &g_Actors[index];
    TASK_SET(e);
    Actor_SelectScript(1);
    g_Task = s;
    Actor_Clear();
}
