#include "area135_14.h"

MATCH void func_801F4464(void) {
    if (g_Task != &D_80143F48) {
        LOW(g_Task->pos.x.fixed) = D_80147C54;
        LOW(g_Task->pos.y.fixed) = D_80147C58;
        g_Task->pos.z.fixed      = D_80147C5C;
    } else {
        g_AreaCameraStep    = 0x20;
        g_AreaScrollTargetX = D_80147C54;
        g_AreaScrollTargetY = D_80147C58;
    }
}
