#include "area172_13.h"

MATCH void func_801F2D48(void) {
    Actor* work                         = g_Task;
    work->tint.signed_bytes.delta.blue  = -1;
    work->tint.signed_bytes.delta.green = -1;
    work->tint.signed_bytes.delta.red   = -1;
    func_801F2DF4(1);
    g_Task->timer       = 4;
    g_Task->header.mode = 4;
}
