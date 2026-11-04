#include "area091_13.h"

MATCH void func_801F312C(void) {
    Actor* temp_s0;
    u32    var_a0;

    ((Actor*)g_SpadWork)->unk_0A += 1;
    if (((Actor*)g_SpadWork)->unk_0A == 0x1E) {
        temp_s0 = ((Actor*)g_SpadWork);
        if (SYS_TestFlag(g_SceneEventFlags, 0x6B) == 0) {
            SYS_SetFlag(g_SceneEventFlags, 0x6BU);
            var_a0 = 0;
        } else {
            var_a0 = 1;
        }
        func_801BE1B0(var_a0);
        g_AreaScrollTargetX  = 0x1F8000;
        g_AreaScrollTargetY  = 0x1A0000;
        ((Actor*)g_SpadWork) = temp_s0;
        g_AreaCameraStep     = 0x20;
        temp_s0->unk_04 += 1;
    }
    func_801F2ED4(((Actor*)g_SpadWork)->unk_0A * 0xA, 0xFF);
}
