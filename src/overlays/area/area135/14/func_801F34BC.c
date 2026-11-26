#include "area135_14.h"

MATCH void func_801F34BC(void) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    s32 sample_w;
    s32 sample_h;
    s16 x;
    s16 y;
    u8  step;

    SELF(Actor)->timer++;
    if (SELF(Actor)->unk_06 != 0) {
        step     = SELF(Actor)->timer;
        sample_w = step * 0x19;
        x        = D_801F6210 + ((0xC8 - sample_w) / 2);
        sample_h = step * 6;
        y        = D_801F6212 + ((0x30 - sample_h) >> 1);
        UI_WindowDrawBoxOutline(x, y, sample_w, sample_h);
    }
    if (SELF(Actor)->timer == 8) {
        SELF(Actor)->header.mode = 2;
    }
}
