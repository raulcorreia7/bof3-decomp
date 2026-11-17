#include "area141_13.h"

MATCH void func_801F35E4(void) {
    s32 scale;

    scale = (g_Task->pos.x.fixed - 0x450000) >> 15;
    if (scale != 0) {
        g_ScriptState->unk_07 = ABS(scale);
        g_Task->direction     = 7;
        if (g_Task == &D_80143F48) {
            Area_SetFacingOffsetX(D_80143F48.direction);
        } else {
            Area_MoveActorRoute(g_ScriptState, g_Task->direction);
        }
    }
}
