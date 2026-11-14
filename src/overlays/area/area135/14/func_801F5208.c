#include "area135_14.h"

s32 func_801F603C(s32 x, s32 y);

MATCH s32 func_801F5208(s32 x, s32 y) {
    u8 v;

    v = D_80143F03;
    if (v != 4 && (u8)(v - 6) >= 2) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0xC) == 0) {
        return 0;
    }
    if ((u8)func_801F603C(x, y) == 0) {
        return 0;
    }
    func_801BE1B0(0);
    return 1;
}
