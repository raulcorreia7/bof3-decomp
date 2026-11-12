#include "area048_13.h"

MATCH void func_801F48DC(void) {
    g_Task->direction_08  = FACING_DOWN;
    g_ScriptState->unk_07 = D_8014686B * 4;
    if (g_ScriptState->unk_07 != 0) {
        if (Actor_GetType() != 2) {
            func_801ABBA8(g_ScriptState, g_Task->direction_08);
            g_ScriptState->flag_00 |= 0x80;
        } else {
            func_801C5DFC(g_Task->direction_08);
            g_AreaCameraHeightStep = 0;
            g_ScriptState->flag_00 |= 0x40;
        }
    }
    g_Task->vz               = 0;
    COORD_INT(g_Task->pos.z) = 0x480;
}
