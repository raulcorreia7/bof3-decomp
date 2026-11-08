#include "game_00.h"

MATCH void func_801C5BB8(void) {
    u8* flags;
    /* FAKE: pin scroll cell pointer to v0. */
    FAKE_REG(s32*, value, "$2");

    if (g_AreaCameraMoving == 0) {
        flags = &D_80143FBC;
        if ((*flags & 0x40) == 0) {
            Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        }
        D_80143FC3 = 0;
        D_80143F4A = 0;
        *flags &= 0xBF;
        func_801C5874();
    } else {
        value = &D_80143F84;
        *value += D_80143F5C;
        Area_AdvanceScroll(g_ScrollHeight);
    }
}
