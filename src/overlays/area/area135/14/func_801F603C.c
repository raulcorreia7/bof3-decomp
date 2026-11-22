#include "area135_14.h"

MATCH s32 func_801F603C(s32 x, s32 y) {
    u8  timer;
    s32 step_x;
    s32 step_y;
    s32 dx;
    s32 dy;
    s32 range;

    timer  = D_80147C29;
    step_x = D_80147C2C * timer;
    step_y = D_80147C30 * timer;
    dx     = abs(x - (D_80147C54 + step_x));
    dy     = y - (D_80147C58 + step_y);
    range  = (g_Task->voice_flags.scene_flag + D_80147C90 + 2) << 15;
    if (dx < range) {
        if (abs(dy) < range) {
            return 1;
        }
    }
    return 0;
}
