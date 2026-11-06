#include "area135_14.h"

MATCH void func_801F4D0C(void) {
    g_Task->direction_08  = FACING_DOWN;
    g_ScriptState->unk_07 = (0x148000 - g_Task->pos.y.fixed) >> 0xF;
    func_801ABBA8(g_ScriptState, g_Task->direction_08);
    g_Task->vz     = 0;
    g_Task->unk_04 = 0;
}
