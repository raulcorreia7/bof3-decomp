#include "area030_04.h"

/* When flag `g_AreaCameraMoving` is clear, arms the spin state: writes 0x40
 * to halfword `g_AreaCameraSpeed` and 0x3C0000 to word `g_AreaScrollTargetY`, then increments
 * byte 0x03 of the scratchpad work object. */
MATCH void func_801DAE3C(void) {
    if (g_AreaCameraMoving == 0) {
        g_AreaCameraSpeed              = 0x40;
        g_AreaScrollTargetCoordY.fixed = TO_COORD(60);
        TASK(Actor)->unk_03 += 1;
    }
}
