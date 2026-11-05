#include "area144_13.h"

MATCH void func_801F3A20(void) {
    s32 diff;

    diff = (0x1D8000 - g_Task->y.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->unk_07 = abs(diff);
        if (diff < 0) {
            g_Task->direction_08 = 1;
        } else {
            g_Task->direction_08 = 5;
        }
        func_801ABBA8(g_ScriptState, g_Task->direction_08);
    }
}
