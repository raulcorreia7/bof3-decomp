#include "game_00.h"

MATCH void func_801C5CB4(void) {
    u8* addr;
    u8  val;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
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
        Area_AdvanceScroll(HIH(D_80143F84));
    }
}
