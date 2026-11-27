#include "area175_13.h"

MATCH void func_801F3644(void) {
    u8 mode;

    func_801F36DC((s16)SELF(Actor)->screen_x, SELF(Actor)->screen_y, SELF(Actor)->timer);
    ACTOR_COUNT_DOWN(SELF(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        SELF(Actor)->header.mode += 1;
    }
}
