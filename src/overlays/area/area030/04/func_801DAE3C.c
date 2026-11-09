#include "area030_04.h"

/* When flag `g_AreaCameraMoving` is clear, arms the spin state. */
MATCH void func_801DAE3C(void) {
    if (g_AreaCameraMoving == 0) {
        g_AreaCameraStep    = 0x40;
        g_AreaScrollTargetY = TO_COORD(60);
        g_Task->unk_03 += 1;
    }
}
