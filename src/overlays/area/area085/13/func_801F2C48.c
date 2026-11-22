#include "area085_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    TASK(Actor)->timer       = 12;
    TASK(Actor)->header.mode = 1;
    TASK(Actor)->header.step = 0;
    work                     = TASK(Actor);
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
    Area_DrawScreenTint();
    func_801F2FCC();
}
