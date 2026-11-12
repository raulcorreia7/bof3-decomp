#include "area098_13.h"

MATCH void func_801F3F50(void) {
    u16 level;
    s32 fade;

    if ((s16)g_Task->screen_y == 90) {
        SND_PlayCue(0x201);
    }
    level            = g_Task->screen_y;
    g_Task->screen_y = level + 1;
    if ((s16)(level + 1) >= 91) {
        fade = (level - 89) * 4;
        if ((s16)fade >= 256) {
            fade = 255;
        }
        func_801F5050(fade & BYTE_MASK);
    }
    if ((func_801F4E7C() & BYTE_MASK) == 0) {
        g_Task->screen_x = 90;
        g_Task->header.mode++;
    }
}
