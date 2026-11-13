#include "area135_14.h"

MATCH void func_801F4D0C(void) {
    g_Task->direction_08  = FACING_DOWN;
    g_ScriptState->unk_07 = (TO_COORD(20) + COORD_HALF - g_Task->pos.y.fixed) >> 0xF;
    Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    g_Task->vz     = 0;
    g_Task->unk_04 = 0;
}
