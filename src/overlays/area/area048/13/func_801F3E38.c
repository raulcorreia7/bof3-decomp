#include "area048_13.h"

MATCH void func_801F3E38(void) {
    if (((COORD_INT(SELF(Actor)->pos.x) == 0) && (SYS_TestFlag(g_SceneEventFlags, 13) != 0)) || ((COORD_INT(SELF(Actor)->pos.x) != 0) && (D_8014686B != 0))) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0D));
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
}
