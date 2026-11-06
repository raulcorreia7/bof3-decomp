#include "area080_13.h"

MATCH void func_801F3BF4(void) {
    g_MessageRequest = D_801F4494[g_MessageChoice];
    switch (g_MessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0xA;
            break;
    }
}
