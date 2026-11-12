#include "area049_14.h"

MATCH s32 func_801F2C04(void) {
    s8 sel;

    sel              = g_MessageChoice;
    g_MessageRequest = D_801F5CD4[sel];
    if (sel == 0) {
        SYS_SetFlag(g_SceneFlags, 59);
    }
}
