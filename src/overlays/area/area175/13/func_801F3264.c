#include "area175_13.h"

MATCH void func_801F3264(void) {
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer != 0) {
        SELF(Actor)->tint.bytes.rgb.r += 6;
        SELF(Actor)->tint.bytes.rgb.g += 6;
        SELF(Actor)->tint.bytes.rgb.b += 6;
    } else {
        MESSAGE_START_WAIT(MSG_AREA175_ASK_REPLAY_SCENE);
        SELF(Actor)->header.mode = 2;
    }
    Area_DrawScreenTint();
}
