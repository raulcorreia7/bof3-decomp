#include "area075_13.h"

/* This function stores the cell; the typed view macro is not an assignable object. */
#undef g_Task

MATCH void func_801F32FC(void) {
    Actor* actor;
    Actor* saved;
    Actor* work;
    s16    slot;
    u8     i;

    actor = (Actor*)g_Task;
    saved = g_CurrentActor;
    for (i = 0; i < 5; i++) {
        slot = SP_REF(s16, 0x0u) = Actor_FindFree();
        if (slot != 0xFF) {
            func_801A4D54(D_801F57B0[i]);
            work               = (Actor*)g_Task;
            work->pos.x.fixed  = actor->pos.x.fixed + TO_COORD(3);
            work->pos.y.fixed  = actor->pos.y.fixed;
            work->pos.z.fixed  = actor->pos.z.fixed;
            work->param.unk_0B = i;
        }
    }
    TASK_SET(actor);
    g_CurrentActor = saved;
}
