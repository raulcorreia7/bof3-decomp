#include "area047_13.h"

MATCH void func_801F38F4(void) {
    SELF(Actor)->pos.x.fixed    = TO_COORD(18);
    g_AreaCamera.scroll_x.fixed = TO_COORD(18);
    SELF(Actor)->pos.y.fixed    = TO_COORD(36);
    g_AreaCamera.scroll_y.fixed = TO_COORD(36);
    Area_InitMapRenderer();
    COORD_INT(SELF(Actor)->pos.z) = 0x1220;
    Area_ScrollAdvance(4640);
    g_AreaCameraAngle.vx = -0x48A;
    D_801492DC           = 0xF8;
}
