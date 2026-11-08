#include "area117_13.h"

MATCH void func_801F3FF0(void) {
    s8 choice;

    /* Tried `if (choice >= 0 && choice < 5)` and a single guard; both changed byte order. */
    choice           = g_MessageChoice;
    g_MessageRequest = D_801F55D8[choice];
    if (choice < 0) {
        goto end;
    }
    if (choice >= 5) {
        goto end;
    }
    g_ScriptVars[0] = 10;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
end:;
}
