#include "area085_13.h"

MATCH void func_801F373C(void) {
    g_ScriptState->steps = ((s32)(TASK(Actor)->pos.x.fixed + TO_COORD(-22)) >> 0xF);
    Area_SetFacingOffsetX(7);
    g_AreaCameraHeightStep = 0;
    TASK(Actor)->vz        = 0;
    g_ScriptState->flags |= 0x40;
    g_AreaScrollTargetY      = TO_COORD(62);
    TASK(Actor)->pos.y.fixed = TO_COORD(62);
}
