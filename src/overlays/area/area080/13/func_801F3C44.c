#include "area080_13.h"

MATCH void func_801F3C44(void) {
    g_UiMessageRequest = D_801F4498[g_UiMessageChoice];
    switch (g_UiMessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0xA;
            break;
    }
}
