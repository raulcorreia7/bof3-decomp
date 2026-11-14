#include "area172_13.h"

MATCH void func_801F2C84(void) {
    Actor* work;
    u8     shade;
    u8     step;

    g_Task->timer -= 1;
    work = g_Task;
    step = work->timer;
    if (step != 0) {
        shade                      = ~(step * 255 / 90);
        work->tint.bytes.rgb.blue  = shade;
        work->tint.bytes.rgb.green = shade;
        work->tint.bytes.rgb.red   = shade;
    } else {
        work->header.mode = 2;
    }
    func_801F2DF4(2);
    func_801F2ED8();
}
