#include "area082_13.h"

MATCH void func_801F4A90(void) {
    if (*g_ScriptVars == 0x26) {
        func_801F5388(0x40);
        D_8014933A = 0;
        Area_DrawGradient(-1);
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step++;
    }
}
