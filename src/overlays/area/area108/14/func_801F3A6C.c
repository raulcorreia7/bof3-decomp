#include "area108_14.h"

MATCH s32 func_801F3A6C(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.rgb.r -= 6;
        g_Task->tint.bytes.rgb.g -= 6;
        g_Task->tint.bytes.rgb.b -= 6;
    } else {
        g_Task->header.mode = 6;
    }
    Area_DrawScreenTint();
    func_801F3C84();
}
