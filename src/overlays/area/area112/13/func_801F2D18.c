#include "area112_13.h"

MATCH void func_801F2D18(void) {
    if (SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(TASK(Actor)->pos.x))) {
        TASK(Actor)->timer            = 0;
        TASK(Actor)->header.step      = 1;
        COORD_INT(TASK(Actor)->pos.y) = -8;
        func_801F2EA8();
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x02));
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    }
    func_801F3274();
}
