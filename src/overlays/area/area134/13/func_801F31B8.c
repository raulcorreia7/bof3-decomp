#include "area134_13.h"

MATCH void func_801F31B8(void) {
    u8* work;
    u8* flag;

    work    = (u8*)g_Task;
    flag    = &g_ScriptVars[1];
    work[1] = 0;
    if (*flag == GAME_NONE || g_ScriptVars[2] == 0x80) {
        *flag = 0;
    }
}
