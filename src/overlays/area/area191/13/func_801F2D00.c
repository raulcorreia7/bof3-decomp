#include "area191_13.h"

MATCH void func_801F2D00(void) {
    u8 mode;

    ACTOR_COUNT_DOWN(mode, timer);
    if (mode & BYTE_MASK) {
        g_Task->tint.bytes.rgb.r += 1;
        g_Task->tint.bytes.rgb.g += 1;
        g_Task->tint.bytes.rgb.b += 1;
    } else {
        MESSAGE_START_WAIT(MSG_134);
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
}
