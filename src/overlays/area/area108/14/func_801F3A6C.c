#include "area108_14.h"

MATCH s32 func_801F3A6C(void) {
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer != 0) {
        SELF(Actor)->tint.bytes.rgb.r -= 6;
        SELF(Actor)->tint.bytes.rgb.g -= 6;
        SELF(Actor)->tint.bytes.rgb.b -= 6;
    } else {
        SELF(Actor)->header.mode = 6;
    }
    Area_DrawScreenTint();
    func_801F3C84();
}
