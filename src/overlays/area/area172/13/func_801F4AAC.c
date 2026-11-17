#include "area172_13.h"

MATCH void func_801F4AAC(void) {
    Actor* work;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->tint.bytes.flags = 1;
    work                     = g_Task;
    work->tint.steps.delta.b = -0x40;
    work->tint.steps.delta.g = -0x40;
    work->tint.steps.delta.r = -0x40;
}
