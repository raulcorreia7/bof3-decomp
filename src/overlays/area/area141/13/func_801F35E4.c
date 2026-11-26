#include "area141_13.h"

MATCH void func_801F35E4(void) {
    s32 scale;

    scale = (SELF(Actor)->pos.x.fixed - 0x450000) >> 15;
    if (scale != 0) {
        g_ScriptState->steps   = ABS(scale);
        SELF(Actor)->direction = 7;
        if (g_Self == &D_80143F48) {
            Area_SetFacingOffsetX(D_80143F48.direction);
        } else {
            Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
        }
    }
}
