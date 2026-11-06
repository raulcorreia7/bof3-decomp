#include "area008_13.h"

MATCH void func_801F2F78(void) {
    u8   tmp;
    u16* halfword;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->header.mode = 9;
        return;
    }
    halfword        = D_80146876;
    g_ScriptVars[2] = 0;
    if (halfword[0] == GAME_NONE) {
        halfword[0] = 0;
        D_801F53F4  = 2;
    }
    tmp        = (D_801F53F4 - 1);
    D_801F53F4 = tmp;
    if (tmp < 2) {
        g_ScriptVars[1]     = 0;
        g_Task->header.mode = 1;
    }
}
