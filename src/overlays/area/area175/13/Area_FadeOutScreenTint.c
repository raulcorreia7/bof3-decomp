#include "area175_13.h"

/* func_801F3374 */
MATCH void Area_FadeOutScreenTint(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.red -= 6;
        g_Task->tint.bytes.rgb.green -= 6;
        g_Task->tint.bytes.rgb.blue -= 6;
    } else {
        g_Task->header.mode = 4;
    }
    Area_DrawScreenTint();
}
