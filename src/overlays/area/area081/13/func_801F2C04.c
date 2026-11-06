#include "area081_13.h"

MATCH s32 func_801F2C04(void) {
    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 2;
            break;
    }
}
