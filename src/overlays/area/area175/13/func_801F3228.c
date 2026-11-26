#include "area175_13.h"

MATCH void func_801F3228(void) {
    Actor* work;

    SELF(Actor)->timer       = 16;
    SELF(Actor)->header.mode = 1;
    work                     = SELF(Actor);
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
}
