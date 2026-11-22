#include "area198_13.h"

MATCH void func_801F2CB8(void) {
    TASK(Actor)->timer += 1;
    func_801F2D28(TASK(Actor)->timer);
    if (TASK(Actor)->timer >= 128) {
        Actor_Clear();
    }
}
