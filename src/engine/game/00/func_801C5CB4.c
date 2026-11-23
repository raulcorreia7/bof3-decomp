#include "game_00.h"

MATCH void func_801C5CB4(void) {
    u8* addr;
    u8  val;

    if (g_AreaCameraMoving == 0) {
        Area_ScrollAdvance(Area_HeightSample(g_AreaCamera.scroll_x.fixed, g_AreaCamera.scroll_y.fixed));
        addr       = &D_80143FBC;
        val        = *addr;
        D_80143F5C = 0;
        D_80143F50 = 0;
        D_80143F4A = 0;
        *addr      = (val & 0xFB);
        return;
    }
    if (D_80143F5C != 0) {
        D_80143F84 += D_80143F5C;
        /* Overlap view: upper half of s32 D_80143F84; sibling TU uses both views.
         */
        Area_ScrollAdvance(HIH(D_80143F84));
    }
}
