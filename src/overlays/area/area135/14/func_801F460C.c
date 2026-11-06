#include "area135_14.h"

MATCH void func_801F460C(void) {
    if (COORD_INT(g_Task->pos.x) >= 6 && (g_InputHeld & PADRdown)) {
        g_Task->direction_08  = FACING_LEFT;
        g_ScriptState->unk_07 = 2;
        func_801ABBA8(g_ScriptState, g_Task->direction_08);
        g_Task->vz = 0;
        g_ScriptState->cursor -= 2;
    }
}
