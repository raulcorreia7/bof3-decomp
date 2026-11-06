#include "area067_14.h"

MATCH void func_801F3E04(void) {
    s8 sel;

    sel              = g_MessageChoice;
    g_MessageRequest = D_801F5384[sel];
    if (sel >= 0) {
        if (sel >= 5) {
            if (sel == 5) {
                g_ScriptVars[0] = 6;
            }
        }
    }
}
