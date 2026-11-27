#include "area085_13.h"

MATCH void func_801F2CB4(void) {
    SELF(Actor)->timer -= 1;
    if (SELF(Actor)->timer != 0) {
        SELF(Actor)->tint.bytes.rgb.r += 4;
        SELF(Actor)->tint.bytes.rgb.g += 4;
        SELF(Actor)->tint.bytes.rgb.b += 4;
    } else {
        SELF(Actor)->timer       = 12;
        SELF(Actor)->header.mode = 3;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
