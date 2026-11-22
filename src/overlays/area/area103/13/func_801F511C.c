#include "area103_13.h"

MATCH void func_801F511C(void) {
    Actor* work = TASK(Actor);

    work->timer++;
    if (TASK(Actor)->timer >= 0x1D) {
        Actor_Clear();
    }
}
