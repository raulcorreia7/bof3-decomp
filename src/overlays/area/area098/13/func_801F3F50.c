#include "area098_13.h"

MATCH void func_801F3F50(void) {
    u16 level;
    s32 fade;

    if (SELF(Actor)->screen_y == 90) {
        SND_SEPlay(0x201);
    }
    level                 = SELF(Actor)->screen_y;
    SELF(Actor)->screen_y = level + 1;
    if ((s16)(level + 1) >= 91) {
        fade = (level - 89) * 4;
        if ((s16)fade >= 256) {
            fade = 255;
        }
        func_801F5050(fade & BYTE_MASK);
    }
    if ((func_801F4E7C() & BYTE_MASK) == 0) {
        SELF(Actor)->screen_x = 90;
        SELF(Actor)->header.mode++;
    }
}
