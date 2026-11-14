#include "area172_13.h"

MATCH void func_801F4AAC(void) {
    Actor* work;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->tint.bytes.flags            = 1;
    work                                = g_Task;
    work->tint.signed_bytes.delta.blue  = -0x40;
    work->tint.signed_bytes.delta.green = -0x40;
    work->tint.signed_bytes.delta.red   = -0x40;
}
