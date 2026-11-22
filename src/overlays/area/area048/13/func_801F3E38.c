#include "area048_13.h"

MATCH void func_801F3E38(void) {
    if (((COORD_INT(TASK(Actor)->pos.x) == 0) && (SYS_TestFlag(g_SceneEventFlags, 13) != 0)) || ((COORD_INT(TASK(Actor)->pos.x) != 0) && (D_8014686B != 0))) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0D));
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}
