#include "area135_14.h"

MATCH void func_801F4178(void) {
    Actor* work;
    u16*   span;

    if (D_80143F03 != 4) {
        work                     = g_Task;
        span                     = (u16*)g_ScriptState;
        work->pos.z.part.integer = (work->pos.z.part.integer + work->vz);
        FIELD(u16, span, 0xA)    = (FIELD(u16, span, 0xA) - 2);
    }
}
