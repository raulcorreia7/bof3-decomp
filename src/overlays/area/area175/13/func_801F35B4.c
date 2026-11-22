#include "area175_13.h"

MATCH void func_801F35B4(void) {
    func_801F36DC((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, TASK(Actor)->timer);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 31U) {
        TASK(Actor)->timer = 30;
        TASK(Actor)->header.mode += 1;
    }
}
