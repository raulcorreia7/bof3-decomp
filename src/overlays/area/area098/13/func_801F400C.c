#include "area098_13.h"

MATCH void func_801F400C(void) {
    u16 level;
    s32 fade;

    level            = g_Task->screen_y;
    g_Task->screen_y = level + 1;
    if ((s16)(level + 1) >= 0x5B) {
        fade = (level - 0x59) * 4;
        if ((s16)fade >= 0x100) {
            fade = 0xFF;
        }
        func_801F5050(fade);
    }
    g_Task->screen_x -= 1;
    if ((s16)g_Task->screen_x == 0) {
        Actor_Clear();
    }
}
