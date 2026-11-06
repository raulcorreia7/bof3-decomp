#include "area198_13.h"

MATCH void func_801F3528(void) {
    s32 diff;

    diff = (0x190000 - g_Task->pos.x.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->unk_07 = abs(diff);
        g_Task->direction_08  = 3;
        func_801ABBA8(g_ScriptState, g_Task->direction_08);
    }
}
