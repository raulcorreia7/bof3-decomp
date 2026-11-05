#include "area135_14.h"

MATCH void func_801F2CD0(void) {
    Actor* actor;
    s32    value;

    actor                = g_Task;
    value                = *(s32*)(D_80147AAC + actor->unk_18 * ACTOR_SIZE);
    actor->unk_09        = 0;
    actor->range_54.word = value;
    g_Task->mode         = 1;
}
