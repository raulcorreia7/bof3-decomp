#include "area135_14.h"

MATCH void func_801F4B0C(void) {
    u8 target;

    target = func_801F5D1C();
    if (target != 4) {
        SELF(Actor)->direction = FACING_RIGHT;
        g_ScriptState->steps   = (((D_801F6B3C[target] << 16) | 0x8000) - SELF(Actor)->pos.x.fixed) >> 15;
        if (g_ScriptState->steps != 0) {
            Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
            SELF(Actor)->vz = 0;
        }
        SELF(Actor)->unk_04 = 0;
    }
}
