#include "area108_14.h"

MATCH s32 func_801F3A6C(void) {
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer != 0) {
        TASK(Actor)->tint.bytes.rgb.r -= 6;
        TASK(Actor)->tint.bytes.rgb.g -= 6;
        TASK(Actor)->tint.bytes.rgb.b -= 6;
    } else {
        TASK(Actor)->header.mode = 6;
    }
    Area_DrawScreenTint();
    func_801F3C84();
}
