#include "area085_13.h"

MATCH void func_801F373C(void) {
    g_ScriptState->unk_07 = ((s32)(g_Task->pos.x.fixed + TO_COORD(-22)) >> 0xF);
    Area_SetFacingOffsetX(7);
    g_AreaCameraHeightStep = 0;
    g_Task->vz             = 0;
    g_ScriptState->flag_00 |= 0x40;
    g_AreaScrollTargetY = TO_COORD(62);
    g_Task->pos.y.fixed = TO_COORD(62);
}
