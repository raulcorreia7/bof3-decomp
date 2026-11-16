#include "area191_13.h"

MATCH void func_801F2D00(void) {
    u8 mode;

    ACTOR_COUNT_DOWN(mode, timer);
    if (mode & BYTE_MASK) {
        g_Task->tint.bytes.rgb.red += 1;
        g_Task->tint.bytes.rgb.green += 1;
        g_Task->tint.bytes.rgb.blue += 1;
    } else {
        MESSAGE_START_WAIT(134);
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
}
