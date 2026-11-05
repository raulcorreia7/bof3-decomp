#include "area198_13.h"

MATCH void func_801F2C80(void) {
    volatile u8* scratch;
    u8           flag;

    flag = g_ScriptVars[0];
    if (flag == 0xDu) {
        scratch    = SP_REF(volatile u8*, 0x44u);
        scratch[2] = (scratch[2] + 1u);
    }
}
