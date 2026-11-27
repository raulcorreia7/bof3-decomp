#include "area117_13.h"

MATCH void func_801F3FF0(void) {
    s8 choice;

    choice             = g_UIMessageChoice;
    g_UIMessageRequest = D_801F55D8[choice];
    if (choice >= 0) {
        if (choice < 5) {
            g_ScriptVars[0] = 10;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
        }
    }
}
