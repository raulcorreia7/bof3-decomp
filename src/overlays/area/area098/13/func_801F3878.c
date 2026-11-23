#include "area098_13.h"

MATCH void func_801F3878(void) {
    u16 scroll;
    u8  remaining;

    scroll                = TASK(Actor)->screen_x + 0x20;
    TASK(Actor)->screen_x = scroll;
    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)scroll, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        TASK(Actor)->timer = 128;
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x09));
    }
}
