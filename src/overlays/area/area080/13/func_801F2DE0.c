#include "area080_13.h"

MATCH void func_801F2DE0(void) {
    u8 remaining;

    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F3870();
    func_801F395C();
    remaining          = SELF(Actor)->timer - 1;
    SELF(Actor)->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = 30;
        SELF(Actor)->header.mode += 1;
    }
}
