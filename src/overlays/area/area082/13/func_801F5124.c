#include "area082_13.h"

MATCH void func_801F5124(void) {
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    SELF(Actor)->unk_32 = (SELF(Actor)->unk_32 - SELF(Actor)->vz / 10000) & 0xFFD;
    func_801F4430();
    if (*g_ScriptVars == 0x3A) {
        SELF(Actor)->header.step++;
    }
}
