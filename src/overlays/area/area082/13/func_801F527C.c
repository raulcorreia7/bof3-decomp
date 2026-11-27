#include "area082_13.h"

MATCH void func_801F527C(void) {
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    if (g_ScriptVars[0] == 0x3B) {
        SELF(Actor)->header.step++;
    }
}
