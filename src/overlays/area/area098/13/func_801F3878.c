#include "area098_13.h"

MATCH void func_801F3878(void) {
    u16 scroll;
    u8  remaining;

    scroll                = SELF(Actor)->screen_x + 0x20;
    SELF(Actor)->screen_x = scroll;
    GFX_DrawColorFan(&SELF(Actor)->angle_x, (s16)scroll, 6);
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = 128;
        SELF(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x09));
    }
}
