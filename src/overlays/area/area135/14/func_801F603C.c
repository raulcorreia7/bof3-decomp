#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F603C(s32 x, s32 y) {
    u8  scale;
    s32 range;
    s32 ax;
    s32 ay;
    s32 dx;
    s32 dy;
    s32 result;

    result = 0;
    scale  = D_80147C29;
    ax     = D_80147C2C * scale;
    ay     = D_80147C30 * scale;
    dx     = x - (D_80147C54 + ax);
    dy     = y - (D_80147C58 + ay);
    if (dx < 0) {
        dx = -dx;
    }

    range = (g_Task->voice_flags.scene_flag + D_80147C90 + 2) << 15;
    if (dx < range) {
        result = abs(dy) < range;
    }

    return result;
}
#else
INCLUDE_ASM(func_801F603C);
#endif
