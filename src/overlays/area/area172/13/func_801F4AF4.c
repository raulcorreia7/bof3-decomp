#include "area172_13.h"

MATCH void func_801F4AF4(void) {
    Actor* work;
    g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->tint.bytes.flags = 0;
    work                     = g_Task;
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
}
