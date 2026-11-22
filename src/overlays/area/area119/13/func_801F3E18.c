#include "area119_13.h"

MATCH void func_801F3E18(void) {
    func_801F3F04(7);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 31U) {
        TASK(Actor)->timer = 31;
        TASK(Actor)->header.step += 1;
    }
}
