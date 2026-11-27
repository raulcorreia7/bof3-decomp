#include "area080_13.h"

MATCH void func_801F3C44(void) {
    g_UIMessageRequest = D_801F4498[g_UIMessageChoice];
    switch (g_UIMessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0xA;
            break;
    }
}
