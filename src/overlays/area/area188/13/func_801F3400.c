#include "area188_13.h"

MATCH void func_801F3400(void) {
    u8 mode;

    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)TASK(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->timer = 32;
        TASK(Actor)->header.mode += 1;
    }
}
