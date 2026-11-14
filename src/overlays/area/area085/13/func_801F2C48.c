#include "area085_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    g_Task->timer              = 12;
    g_Task->header.mode        = 1;
    g_Task->header.step        = 0;
    work                       = g_Task;
    work->tint.bytes.rgb.blue  = 0;
    work->tint.bytes.rgb.green = 0;
    work->tint.bytes.rgb.red   = 0;
    Area_DrawScreenTint();
    func_801F2FCC();
}
