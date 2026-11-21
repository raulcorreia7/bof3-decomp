#include "area080_13.h"

MATCH void func_801F3C94(void) {
    g_UiMessageRequest = D_801F449C[g_UiMessageChoice];
    switch (g_UiMessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0xA;
            break;
    }
}
