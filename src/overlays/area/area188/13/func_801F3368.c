#include "area188_13.h"

MATCH void func_801F3368(void) {
    u16 screen_x;
    u8  mode;

    screen_x              = TASK(Actor)->screen_x + 0x20;
    TASK(Actor)->screen_x = screen_x;
    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)screen_x, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        TASK(Actor)->timer = 128;
        TASK(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x14));
    }
}
