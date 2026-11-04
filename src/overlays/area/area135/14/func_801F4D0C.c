#include "area135_14.h"

MATCH void func_801F4D0C(void) {
    g_SpadWork->direction_08 = 5;
    g_ScriptState->unk_07    = (0x148000 - g_SpadWork->y.fixed) >> 0xF;
    func_801ABBA8(g_ScriptState, g_SpadWork->direction_08);
    g_SpadWork->vz     = 0;
    g_SpadWork->unk_04 = 0;
}
