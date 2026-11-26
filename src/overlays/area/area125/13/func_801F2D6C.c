#include "area125_13.h"

MATCH void func_801F2D6C(void) {
    u8 count;

    if (SELF(Actor)->timer % 15 == 0) {
        func_801F3268(2);
    }
    func_801F33B0();
    ACTOR_COUNT_DOWN(SELF(Actor), count, timer);
    if (count == 0) {
        SELF(Actor)->header.mode += 1;
    }
}
