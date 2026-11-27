#include "area135_14.h"

MATCH void func_801F3ABC(void) {
    if (SYS_TestFlag(&g_SceneEventFlags, 42)) {
        SELF(Actor)->pos.z.fixed = -0x180;
        SELF(Actor)->header.step = 3;
    } else {
        SELF(Actor)->pos.z.fixed = -0x90;
        SELF(Actor)->header.step++;
    }
    func_801F3CA8();
}
