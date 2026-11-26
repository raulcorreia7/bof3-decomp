#include "area103_13.h"

MATCH void func_801F511C(void) {
    Actor* work = SELF(Actor);

    work->timer++;
    if (SELF(Actor)->timer >= 0x1D) {
        Actor_Clear();
    }
}
