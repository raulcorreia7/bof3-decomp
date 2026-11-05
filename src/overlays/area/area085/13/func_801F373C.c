#include "area085_13.h"

MATCH void func_801F373C(void) {
    g_ScriptState->unk_07 = ((s32)(g_Task->x.fixed + 0xFFEA0000) >> 0xF);
    func_801C5DFC(7);
    g_AreaCameraHeightStep = 0;
    g_Task->vz             = 0;
    g_ScriptState->flag_00 |= 0x40;
    g_AreaScrollTargetY = 0x3E0000;
    g_Task->y.fixed     = 0x3E0000;
}
