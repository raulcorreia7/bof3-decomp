#include "area112_13.h"

MATCH void func_801F2E14(void) {
    if (!SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(SELF(Actor)->pos.x))) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step++;
        COORD_INT(SELF(Actor)->pos.y) = 8;
        func_801F2EA8();
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    }
    func_801F3274();
}
