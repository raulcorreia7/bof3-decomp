#include "area013_13.h"

MATCH void func_801F2CEC(void) {
    Actor* work = g_SpadWork;
    s32    diff = 0x1C8000 - work->x.fixed;

    work->direction_08    = diff >= 0 ? 3 : 7;
    g_ScriptState->unk_07 = abs(diff) / 0x8000;
    if (g_ScriptState->unk_07 != 0) {
        func_801ABBA8(g_ScriptState, g_SpadWork->direction_08);
    }
}
