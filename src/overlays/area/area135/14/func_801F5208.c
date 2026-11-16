#include "area135_14.h"

MATCH s32 func_801F5208(s32 x, s32 y) {
    u8 state;

    state = D_80143F03;
    if (state != 4 && (u8)(state - 6) >= 2) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0xC) == 0) {
        return 0;
    }
    if ((u8)func_801F603C(x, y) == 0) {
        return 0;
    }
    Scene_SetupParty(0);
    return 1;
}
