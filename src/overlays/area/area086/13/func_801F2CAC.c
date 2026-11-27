#include "area086_13.h"

MATCH void func_801F2CAC(void) {
    if (SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(SELF(Actor)->pos.x)) != 0) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    }
    func_801F3070();
}
