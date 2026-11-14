#include "area191_13.h"

MATCH void func_801F2CC4(void) {
    Actor* work;

    work                       = g_Task;
    work->tint.bytes.rgb.blue  = 0;
    work->tint.bytes.rgb.green = 0;
    work->tint.bytes.rgb.red   = 0;
    g_Task->timer              = 60;
    g_Task->header.mode        = 1;
}
