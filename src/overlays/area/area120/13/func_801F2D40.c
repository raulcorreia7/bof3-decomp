#include "area120_13.h"

MATCH void func_801F2D40(void) {
    func_801F36B0();
    if (g_ScriptVars[0] == 0x11) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x03));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SELF(Actor)->unk_06 = 2;
        SELF(Actor)->header.mode++;
    }
}
