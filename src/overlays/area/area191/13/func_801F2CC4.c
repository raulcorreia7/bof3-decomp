#include "area191_13.h"

MATCH void func_801F2CC4(void) {
    Actor* work;

    work                   = g_Task;
    work->tint.bytes.rgb.b = 0;
    work->tint.bytes.rgb.g = 0;
    work->tint.bytes.rgb.r = 0;
    g_Task->timer          = 60;
    g_Task->header.mode    = 1;
}
