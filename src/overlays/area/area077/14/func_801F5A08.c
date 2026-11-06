#include "area077_14.h"

MATCH void func_801F5A08(void) {
    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0;
            break;
    }
}
