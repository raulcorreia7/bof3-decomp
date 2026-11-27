#include "area191_13.h"

MATCH void func_801F2CC4(void) {
    Actor* work;

    work                     = SELF(Actor);
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
    SELF(Actor)->timer       = 60;
    SELF(Actor)->header.mode = 1;
}
