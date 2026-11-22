#include "area103_13.h"

MATCH void func_801F44B0(void) {
    if (TASK(Actor)->timer % 5 == 0) {
        func_801F4E70(TASK(Actor)->timer / 5 + 4);
    }
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer / 5 == 3) {
        TASK(Actor)->header.step++;
        TASK(Actor)->timer = 1;
    }
}
