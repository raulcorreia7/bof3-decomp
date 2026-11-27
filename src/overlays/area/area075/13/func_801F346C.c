#include "area075_13.h"

MATCH void func_801F346C(void) {
    s8 blue;

    blue = SELF(Actor)->tint.steps.delta.r;
    if (blue != -0x80) {
        SELF(Actor)->tint.bytes.rgb.r = blue - 8;
        SELF(Actor)->tint.bytes.rgb.g -= 8;
        SELF(Actor)->tint.bytes.rgb.b -= 8;
        SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
        SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
        COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
        g_ScriptState->cursor -= 2;
    } else {
        SELF(Actor)->header.flags = 0;
    }
}
