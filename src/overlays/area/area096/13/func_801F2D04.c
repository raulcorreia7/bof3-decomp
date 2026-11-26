#include "area096_13.h"

MATCH void func_801F2D04(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 32) != 0) {
        g_AreaSceneMode           = 1;
        SELF(Actor)->pos.z.fixed  = -0x100;
        SELF(Actor)->param.unk_0B = 0x80;
        SELF(Actor)->timer        = 10;
        SELF(Actor)->header.step++;
        func_801F2ECC(-0x100, 0x80);
    }
}
