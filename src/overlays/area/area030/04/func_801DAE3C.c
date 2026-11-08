#include "area030_04.h"

/* When flag `g_AreaCameraMoving` is clear, arms the spin state: writes 0x40
 * to halfword `g_AreaCameraStep` and 0x3C0000 to word `g_AreaScrollTargetY`, then increments
 * byte 0x03 of the scratchpad work object. */
MATCH void func_801DAE3C(void) {
    u8* spad_ptr;

    if (g_AreaCameraMoving == 0) {
        spad_ptr            = (u8*)g_Task;
        g_AreaCameraStep    = 0x40;
        g_AreaScrollTargetY = TO_COORD(60);
        spad_ptr[3] += 1;
    }
}
