#include "area082_13.h"

MATCH void func_801F4D6C(void) {
    if (g_ScriptVars[0] == 0x32) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x08));
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step++;
    }
}
