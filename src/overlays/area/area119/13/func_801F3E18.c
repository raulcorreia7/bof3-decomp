#include "area119_13.h"

MATCH void func_801F3E18(void) {
    func_801F3F04(7);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 31U) {
        SELF(Actor)->timer = 31;
        SELF(Actor)->header.step += 1;
    }
}
