#include "area120_13.h"

MATCH void func_801F3D14(void) {
    u8 step;

    SELF(Actor)->timer += 2;
    step = SELF(Actor)->timer;
    func_801F3F5C(0x80 - (step * 2), 0x40 - step, 1, 0);
    if (SELF(Actor)->timer >= 64U) {
        Actor_Clear();
    }
}
