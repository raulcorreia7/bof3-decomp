#include "game_00.h"

MATCH void func_801C5BB8(void) {
    u8*  flags;
    s32* value;

    if (g_AreaCameraMoving == 0) {
        flags = &D_80143FBC;
        if ((*flags & 0x40) == 0) {
            Area_ScrollAdvance(Area_HeightSample(g_AreaCamera.scroll_x.fixed, g_AreaCamera.scroll_y.fixed));
        }
        D_80143FC3 = 0;
        D_80143F4A = 0;
        *flags &= 0xBF;
        func_801C5874();
    } else {
        value = &g_PartyPos.z.fixed;
        *value += D_80143F5C;
        Area_ScrollAdvance(COORD_INT(g_PartyPos.z));
    }
}
