#include "area102_13.h"

MATCH void func_801F3630(void) {
    func_801F36B4(SELF(Actor)->timer >> 2);
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer < 8U) {
        SELF(Actor)->timer       = SELF(Actor)->unk_0A;
        SELF(Actor)->header.step = 1;
    }
}
