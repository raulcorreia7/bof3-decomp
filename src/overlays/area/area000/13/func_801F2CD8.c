#include "area000_13.h"

MATCH void func_801F2CD8(void) {
    u8* spad;
    s32 value;

    spad = (u8*)g_Task;
    func_801ABBA8((void*)g_ScriptState, spad[8]);
    value                   = 2;
    ((u8*)g_ScriptState)[7] = value;
}
