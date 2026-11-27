#include "area175_13.h"

MATCH void func_801F35B4(void) {
    func_801F36DC((s16)SELF(Actor)->screen_x, SELF(Actor)->screen_y, SELF(Actor)->timer);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 31U) {
        SELF(Actor)->timer = 30;
        SELF(Actor)->header.mode += 1;
    }
}
