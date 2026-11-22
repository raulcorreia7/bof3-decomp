#include "area042_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C84(void) {
    s16 height;
    s32 value;
    FAKE_STACK_PADS(u8, 16); /* FAKE: retail's frame is 0x28, the body's locals take 0x18. */

    height                   = Area_HeightSample(g_Task->vx, g_Task->vy);
    value                    = (height << 0x10) + TO_COORD(0x100);
    g_Task->vz               = value;
    g_Task->gravity          = value;
    COORD_INT(g_Task->pos.z) = height;
    g_Task->voice_flags.raw  = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
        g_Task->header.mode = 1;
    } else {
        g_Task->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F2C84);
#endif
