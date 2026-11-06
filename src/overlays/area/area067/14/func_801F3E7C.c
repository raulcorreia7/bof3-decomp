#include "area067_14.h"

MATCH void func_801F3E7C(void) {
    s8 sel;

    sel              = g_MessageChoice;
    g_MessageRequest = D_801F539C[sel];
    if (sel < 2) {
        if (sel >= 0) {
            g_ScriptVars[0] = 5;
        }
    }
}
