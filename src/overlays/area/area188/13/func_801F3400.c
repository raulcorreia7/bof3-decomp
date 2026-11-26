#include "area188_13.h"

MATCH void func_801F3400(void) {
    u8 mode;

    GFX_DrawColorFan(&SELF(Actor)->angle_x, (s16)SELF(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(SELF(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.mode += 1;
    }
}
