#include "area091_13.h"

MATCH void func_801F312C(void) {
    Actor* actor;
    u32    value;

    ((Actor*)g_SpadWork)->unk_0A += 1;
    if (((Actor*)g_SpadWork)->unk_0A == 0x1E) {
        actor = ((Actor*)g_SpadWork);
        if (SYS_TestFlag(g_SceneEventFlags, 0x6B) == 0) {
            SYS_SetFlag(g_SceneEventFlags, 0x6BU);
            value = 0;
        } else {
            value = 1;
        }
        func_801BE1B0(value);
        g_AreaScrollTargetX  = 0x1F8000;
        g_AreaScrollTargetY  = 0x1A0000;
        ((Actor*)g_SpadWork) = actor;
        g_AreaCameraStep     = 0x20;
        actor->unk_04 += 1;
    }
    func_801F2ED4(((Actor*)g_SpadWork)->unk_0A * 0xA, 0xFF);
}
