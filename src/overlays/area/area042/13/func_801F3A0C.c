#include "area042_13.h"

MATCH void func_801F3A0C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(TASK(Actor)->pos.x)]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}
