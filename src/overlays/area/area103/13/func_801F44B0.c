#include "area103_13.h"

MATCH void func_801F44B0(void) {
    if (SELF(Actor)->timer % 5 == 0) {
        func_801F4E70(SELF(Actor)->timer / 5 + 4);
    }
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer / 5 == 3) {
        SELF(Actor)->header.step++;
        SELF(Actor)->timer = 1;
    }
}
