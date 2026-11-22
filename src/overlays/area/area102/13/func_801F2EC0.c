#include "area102_13.h"

MATCH void func_801F2EC0(void) {
    func_801F2F44(TASK(Actor)->timer >> 2);
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer < 8U) {
        TASK(Actor)->timer       = TASK(Actor)->unk_0A;
        TASK(Actor)->header.step = 1;
    }
}
