#include "area188_13.h"

MATCH void func_801F3400(void) {
    u8 mode;

    GFX_DrawColorFan(&g_Task->unk_64, (s16)g_Task->screen_x, 6);
    ACTOR_COUNT_DOWN(mode, timer);
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 32;
        g_Task->header.mode += 1;
    }
}
