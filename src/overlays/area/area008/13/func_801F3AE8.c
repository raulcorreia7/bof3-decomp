#include "area008_13.h"

MATCH void func_801F3AE8(void) {
    func_801F3C2C();
    func_801F3D18();

    TASK(Actor)->tint.steps.delta.r = (TASK(Actor)->tint.steps.delta.r - 1);
    if (TASK(Actor)->tint.steps.delta.r < 0) {
        TASK(Actor)->tint.steps.delta.r = 0x1D;
        TASK(Actor)->tint.steps.delta.g = (TASK(Actor)->tint.steps.delta.g - 1);
    }
    if (TASK(Actor)->tint.steps.delta.g < 0) {
        TASK(Actor)->tint.steps.delta.r = 0;
        TASK(Actor)->tint.steps.delta.g = 0;
        TASK(Actor)->header.mode        = (TASK(Actor)->header.mode + 1);
    }
}
