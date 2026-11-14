#include "area175_13.h"

MATCH void func_801F3228(void) {
    Actor* work;

    g_Task->timer              = 16;
    g_Task->header.mode        = 1;
    work                       = g_Task;
    work->tint.bytes.rgb.blue  = 0;
    work->tint.bytes.rgb.green = 0;
    work->tint.bytes.rgb.red   = 0;
}
