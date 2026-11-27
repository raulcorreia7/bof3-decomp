#include "area172_13.h"

MATCH void func_801F3034(void) {
    Actor* work;

    work           = SELF(Actor);
    work->timer    = 8;
    work->screen_x = 0;
    SELF(Actor)->header.mode++;
}
