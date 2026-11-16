#include "area042_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C84(void) {
    FAKE_STACK_PADS(u8, 16); /* FAKE: retail frame is 16 bytes larger with no access. */
    s16 height;

    height                   = Area_SampleHeight(g_Task->vx, g_Task->vy);
    g_Task->vz               = TO_COORD(height) + TO_COORD(256);
    g_Task->gravity          = TO_COORD(height) + TO_COORD(256);
    COORD_INT(g_Task->pos.z) = height;
    g_Task->state_70.word    = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
        g_Task->header.mode = 1;
    } else {
        g_Task->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F2C84);
#endif
