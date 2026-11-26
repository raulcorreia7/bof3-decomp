#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 remaining;

    GFX_DrawColorFan(&SELF(Actor)->angle_x, (s16)SELF(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.mode += 1;
    }
}
