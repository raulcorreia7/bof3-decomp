#include "area191_13.h"

MATCH void func_801F2CC4(void) {
    Actor* work;

    work                     = TASK(Actor);
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
    TASK(Actor)->timer       = 60;
    TASK(Actor)->header.mode = 1;
}
