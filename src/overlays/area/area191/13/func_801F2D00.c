#include "area191_13.h"

MATCH void func_801F2D00(void) {
    u8 mode;

    ACTOR_COUNT_DOWN(SELF(Actor), mode, timer);
    if (mode & BYTE_MASK) {
        SELF(Actor)->tint.bytes.rgb.r += 1;
        SELF(Actor)->tint.bytes.rgb.g += 1;
        SELF(Actor)->tint.bytes.rgb.b += 1;
    } else {
        MESSAGE_START_WAIT(MSG_AREA191_RAKDA_SACRIFICE);
        SELF(Actor)->header.mode = 2;
    }
    Area_DrawScreenTint();
}
