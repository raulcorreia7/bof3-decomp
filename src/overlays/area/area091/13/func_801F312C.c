#include "area091_13.h"

MATCH void func_801F312C(void) {
    Actor* actor;
    u32    value;

    SELF(Actor)->unk_0A += 1;
    if (SELF(Actor)->unk_0A == 0x1E) {
        actor = SELF(Actor);
        if (SYS_TestFlag(g_SceneEventFlags, 107) == 0) {
            SYS_SetFlag(g_SceneEventFlags, 107U);
            value = 0;
        } else {
            value = 1;
        }
        Scene_SetupParty(value);
        g_AreaCamera.scroll_x.fixed = TO_COORD(31) + COORD_HALF;
        g_AreaCamera.scroll_y.fixed = TO_COORD(26);
        g_Self                      = actor;
        g_AreaCameraSpeed           = 0x20;
        actor->unk_04 += 1;
    }
    func_801F2ED4(SELF(Actor)->unk_0A * 0xA, 0xFF);
}
