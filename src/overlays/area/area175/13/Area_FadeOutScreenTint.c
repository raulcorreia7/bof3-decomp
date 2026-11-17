#include "area175_13.h"

/* func_801F3374 */
MATCH void Area_FadeOutScreenTint(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.r -= 6;
        g_Task->tint.bytes.rgb.g -= 6;
        g_Task->tint.bytes.rgb.b -= 6;
    } else {
        g_Task->header.mode = 4;
    }
    Area_DrawScreenTint();
}
