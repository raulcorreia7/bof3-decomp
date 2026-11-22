#include "area075_13.h"

/* This function stores the cell; the typed view macro is not an assignable object. */
#undef g_Task

MATCH void func_801F32FC(void) {
    Actor* actor;
    Actor* saved;
    Actor* work;
    s16    slot;
    u8     i;

    actor = TASK(Actor);
    saved = g_CurrentActor;
    for (i = 0; i < 5; i++) {
        slot = SP_REF(s16, 0x0u) = Actor_FindFreeField();
        if (slot != 0xFF) {
            Actor_SpawnFromRecord(D_801F57B0[i]);
            work               = TASK(Actor);
            work->pos.x.fixed  = actor->pos.x.fixed + TO_COORD(3);
            work->pos.y.fixed  = actor->pos.y.fixed;
            work->pos.z.fixed  = actor->pos.z.fixed;
            work->param.unk_0B = i;
        }
    }
    TASK_SET(actor);
    g_CurrentActor = saved;
}
