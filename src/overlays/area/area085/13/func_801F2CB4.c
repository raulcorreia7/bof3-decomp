#include "area085_13.h"

MATCH void func_801F2CB4(void) {
    TASK(Actor)->timer -= 1;
    if (TASK(Actor)->timer != 0) {
        TASK(Actor)->tint.bytes.rgb.r += 4;
        TASK(Actor)->tint.bytes.rgb.g += 4;
        TASK(Actor)->tint.bytes.rgb.b += 4;
    } else {
        TASK(Actor)->timer       = 12;
        TASK(Actor)->header.mode = 3;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
