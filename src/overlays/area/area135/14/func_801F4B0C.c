#include "area135_14.h"

MATCH void func_801F4B0C(void) {
    u8 target;

    target = func_801F5D1C();
    if (target != 4) {
        g_Task->direction_08  = FACING_RIGHT;
        g_ScriptState->unk_07 = (((D_801F6B3C[target] << 16) | 0x8000) - g_Task->pos.x.fixed) >> 15;
        if (g_ScriptState->unk_07 != 0) {
            Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
            g_Task->vz = 0;
        }
        g_Task->unk_04 = 0;
    }
}
