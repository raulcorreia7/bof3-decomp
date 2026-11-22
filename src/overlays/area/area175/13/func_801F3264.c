#include "area175_13.h"

MATCH void func_801F3264(void) {
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer != 0) {
        TASK(Actor)->tint.bytes.rgb.r += 6;
        TASK(Actor)->tint.bytes.rgb.g += 6;
        TASK(Actor)->tint.bytes.rgb.b += 6;
    } else {
        MESSAGE_START_WAIT(MSG_AREA175_ASK_REPLAY_SCENE);
        TASK(Actor)->header.mode = 2;
    }
    Area_DrawScreenTint();
}
