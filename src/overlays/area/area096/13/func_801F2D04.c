#include "area096_13.h"

MATCH void func_801F2D04(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 32) != 0) {
        g_AreaSceneMode           = 1;
        TASK(Actor)->pos.z.fixed  = -0x100;
        TASK(Actor)->param.unk_0B = 0x80;
        TASK(Actor)->timer        = 10;
        TASK(Actor)->header.step++;
        func_801F2ECC(-0x100, 0x80);
    }
}
