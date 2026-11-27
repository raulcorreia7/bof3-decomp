#include "area117_13.h"

MATCH void func_801F4048(void) {
    s8 choice = g_UIMessageChoice;

    g_UIMessageRequest = D_801F55E4[choice];
    switch (choice) {
        case 0:
        case 1:
        case 3:
        case 4:
            g_ScriptVars[0] = 10;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
            break;
        case 2:
            g_ScriptVars[0] = 20;
            break;
        case 5:
            break;
    }
}
