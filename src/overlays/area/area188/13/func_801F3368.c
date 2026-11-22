#include "area188_13.h"

MATCH void func_801F3368(void) {
    u16 screen_x;
    u8  mode;

    screen_x         = g_Task->screen_x + 0x20;
    g_Task->screen_x = screen_x;
    GFX_DrawColorFan(&g_Task->unk_64, (s16)screen_x, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 128;
        g_Task->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x14));
    }
}
