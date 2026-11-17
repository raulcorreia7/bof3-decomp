#include "area141_13.h"

MATCH void func_801F36CC(void) {
    Actor* task;

    task = g_Task;
    task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    /* FAKE: retail reloads the work pointer between the flag update and the tint stores. */
    task                     = g_Task;
    task->tint.steps.delta.b = -60;
    task->tint.steps.delta.g = -60;
    task->tint.steps.delta.r = -60;
    g_Task->tint.bytes.flags = 1;
    func_801F3740();
    g_Task->unk_04 = 1;
}
