#include "area144_13.h"

MATCH void func_801F3B24(void) {
    s32 diff;

    diff = (0x1C0000 - g_SpadWork->y.fixed) >> 15;
    if (diff != 0) {
        g_SpadWork->direction_08 = 1;
        g_ScriptState->unk_07    = abs(diff);
        func_801ABBA8(g_ScriptState, g_SpadWork->direction_08);
    }
    g_GameFlags |= 8;
}
