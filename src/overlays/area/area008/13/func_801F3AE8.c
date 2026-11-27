#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    SELF(Actor)->tint.steps.delta.r = (SELF(Actor)->tint.steps.delta.r - 1);
    if (SELF(Actor)->tint.steps.delta.r < 0) {
        SELF(Actor)->tint.steps.delta.r = 0x1D;
        SELF(Actor)->tint.steps.delta.g = (SELF(Actor)->tint.steps.delta.g - 1);
    }
    if (SELF(Actor)->tint.steps.delta.g < 0) {
        SELF(Actor)->tint.steps.delta.r = 0;
        SELF(Actor)->tint.steps.delta.g = 0;
        SELF(Actor)->header.mode        = (SELF(Actor)->header.mode + 1);
    }
}
