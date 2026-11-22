#include "area175_13.h"

MATCH void func_801F3644(void) {
    u8 mode;

    func_801F36DC((s16)TASK(Actor)->screen_x, (s16)TASK(Actor)->screen_y, TASK(Actor)->timer);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->header.mode += 1;
    }
}
