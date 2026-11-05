#include "area135_14.h"

MATCH void func_801F4178(void) {
    Actor* work;
    u16*   span;

    if (D_80143F03 != 4) {
        work                   = g_Task;
        span                   = (u16*)g_ScriptState;
        FIELD(u16, work, 0x3E) = (u16)(FIELD(u16, work, 0x3E) + work->vz);
        FIELD(u16, span, 0xA)  = (u16)(FIELD(u16, span, 0xA) - 2);
    }
}
