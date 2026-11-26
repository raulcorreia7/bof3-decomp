#include "area085_13.h"

MATCH void func_801F373C(void) {
    g_ScriptState->steps = ((s32)(SELF(Actor)->pos.x.fixed + TO_COORD(-22)) >> 0xF);
    Area_SetFacingOffsetX(7);
    g_AreaCameraHeightDelta = 0;
    SELF(Actor)->vz         = 0;
    g_ScriptState->flags |= 0x40;
    g_AreaScrollTargetY      = TO_COORD(62);
    SELF(Actor)->pos.y.fixed = TO_COORD(62);
}
