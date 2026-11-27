#include "area079_13.h"

MATCH void func_801F2D20(void) {
    s8 choice = g_UIMessageChoice;

    g_UIMessageRequest = D_801F4C70[choice];
    switch (choice) {
        case 0:
            g_ScriptVars[3] = 11;
            break;
        case 1:
            g_ScriptVars[3] = 12;
            break;
        case 2:
            g_ScriptVars[3] = 13;
            break;
        case 3:
            g_ScriptVars[3] = 14;
            break;
        case 4:
            g_ScriptVars[3] = 15;
            break;
        case 5:
            g_ScriptVars[3] = 16;
            break;
    }
}
