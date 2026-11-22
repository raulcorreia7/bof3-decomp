#include "area102_13.h"

MATCH void func_801F3630(void) {
    func_801F36B4(TASK(Actor)->timer >> 2);
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer < 8U) {
        TASK(Actor)->timer       = TASK(Actor)->unk_0A;
        TASK(Actor)->header.step = 1;
    }
}
