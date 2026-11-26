#include "area172_13.h"

MATCH void func_801F2C84(void) {
    Actor* work;
    u8     shade;
    u8     step;

    SELF(Actor)->timer -= 1;
    work = SELF(Actor);
    step = work->timer;
    if (step != 0) {
        shade                  = ~(step * 255 / 90);
        work->tint.bytes.rgb.b = shade;
        work->tint.bytes.rgb.g = shade;
        work->tint.bytes.rgb.r = shade;
    } else {
        work->header.mode = 2;
    }
    func_801F2DF4(2);
    func_801F2ED8();
}
