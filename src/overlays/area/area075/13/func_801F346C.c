#include "area075_13.h"

MATCH void func_801F346C(void) {
    s8 blue;

    blue = TASK(Actor)->tint.steps.delta.r;
    if (blue != -0x80) {
        TASK(Actor)->tint.bytes.rgb.r = blue - 8;
        TASK(Actor)->tint.bytes.rgb.g -= 8;
        TASK(Actor)->tint.bytes.rgb.b -= 8;
        TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
        TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
        COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
        g_ScriptState->cursor -= 2;
    } else {
        TASK(Actor)->header.flags = 0;
    }
}
