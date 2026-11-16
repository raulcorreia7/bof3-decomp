#include "area175_13.h"

MATCH void func_801F3264(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.red += 6;
        g_Task->tint.bytes.rgb.green += 6;
        g_Task->tint.bytes.rgb.blue += 6;
    } else {
        MESSAGE_START_WAIT(31);
        g_Task->header.mode = 2;
    }
    Area_DrawScreenTint();
}
