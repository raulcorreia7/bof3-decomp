#include "area135_14.h"

MATCH void func_801F4C18(void) {
    Actor* work;

    g_SpadWork->direction_08 = 7;
    g_ScriptState->unk_07    = (u8)((s32)(g_SpadWork->x.fixed + 0xFFE38000) >> 0xF);
    if ((s8)g_ScriptState->unk_07 < 0) {
        g_SpadWork->direction_08 ^= 4;
        g_ScriptState->unk_07 = (u8) - (s32)g_ScriptState->unk_07;
    }
    func_801ABBA8(g_ScriptState, (s32)g_SpadWork->direction_08);
    work = g_SpadWork;
    work->unk_04 += 1;
    work->vz = 0;
    g_ScriptState->cursor -= 2;
}
