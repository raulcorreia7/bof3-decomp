#include "area008_13.h"

MATCH void func_801F3BB4(void) {
    u8* p;
    u8  flag;

    p    = &g_ScriptVars[3];
    flag = *p;
    if (flag >= 0x10) {
        *p = (flag | 0x80);
        g_ScriptVars[2] |= 0x80;
        SND_StopSequence(0, 2);
    } else {
        *p = (flag | 0x80);
        SND_StopSequence(0, 2);
    }
    Actor_Clear();
}
