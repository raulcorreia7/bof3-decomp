#include "area149_13.h"

MATCH void func_801F36CC(void) {
    s32 y;
    s32 x;

    if (D_80143F04 == 0x94) {
        D_80147A8E += 22;
        y = g_AreaFocusY;
        /* FAKE: keeps the focus x load after the integer-half store; pure C differs in 11 rows. */
        FAKE_BARRIER();
        x               = D_80147A8C;
        D_80147ACF      = 1;
        D_80147AD6      = 0;
        D_80147A96      = Area_SampleHeight(x, y);
        g_AreaSceneMode = 1;
        if (SYS_TestFlag(D_80144EF8, 0x11) != 0) {
            g_SceneEventMode = 0x21;
            g_SceneEventStep = 0;
            D_801448EE       = 0x5A;
        }
    }
    if (D_80143F04 == 0xA7) {
        D_80147ACF       = 2;
        g_AreaSceneMode  = 2;
        g_SceneEventMode = 0x21;
        g_SceneEventStep = 0xA;
        D_80147AD6       = 0;
        D_801448EE       = 0x5A;
    }
}
