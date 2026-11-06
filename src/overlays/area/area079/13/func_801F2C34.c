#include "area079_13.h"

MATCH void func_801F2C34(void) {
    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0x14;
            break;
    }
}
