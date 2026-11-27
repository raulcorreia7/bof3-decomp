#include "area135_14.h"

MATCH void func_801F4178(void) {
    Actor* work;
    u16*   span;

    if (g_GameCellType != 4) {
        work                     = SELF(Actor);
        span                     = (u16*)g_ScriptState;
        work->pos.z.part.integer = (work->pos.z.part.integer + work->vz);
        FIELD(u16, span, 0xA)    = (FIELD(u16, span, 0xA) - 2);
    }
}
