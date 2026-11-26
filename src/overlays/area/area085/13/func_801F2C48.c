#include "area085_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    SELF(Actor)->timer       = 12;
    SELF(Actor)->header.mode = 1;
    SELF(Actor)->header.step = 0;
    work                     = SELF(Actor);
    work->tint.bytes.rgb.b   = 0;
    work->tint.bytes.rgb.g   = 0;
    work->tint.bytes.rgb.r   = 0;
    Area_DrawScreenTint();
    func_801F2FCC();
}
