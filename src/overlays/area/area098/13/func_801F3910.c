#include "area098_13.h"

MATCH void func_801F3910(void) {
    u8 remaining;

    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)TASK(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        TASK(Actor)->timer = 32;
        TASK(Actor)->header.mode += 1;
    }
}
