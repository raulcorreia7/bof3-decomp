#include "area135_14.h"

MATCH void func_801F456C(void) {
    if (COORD_INT(g_Task->pos.y) >= 7 && (g_InputHeld & PADRdown)) {
        g_Task->direction_08  = FACING_UP;
        g_ScriptState->unk_07 = 2;
        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
        g_Task->vz = 0;
        g_ScriptState->cursor -= 2;
    }
}
