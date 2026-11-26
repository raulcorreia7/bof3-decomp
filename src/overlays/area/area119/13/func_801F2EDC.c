#include "area119_13.h"

/* Clears the work halfword, routes the state by the overlay flag and the camera,
 * then draws. */
MATCH void func_801F2EDC(void) {
    /* The map bundle's fixed address; its width is the cell row stride. */
    u8* bundle;
    s32 dx;
    s16 span;

    SELF(Actor)->screen_y = 0;
    if (SYS_TestFlag(D_80144ED0, 0x0F) == 0) {
        bundle                                 = MEM_PTR(u8, MAP_BUNDLE_BASE);
        g_AreaCellCodes[bundle[0] * 62 + 0x41] = 0x52;
        g_AreaCellCodes[bundle[0] * 63 + 0x41] = 0x52;
        SELF(Actor)->header.step               = 5;
    } else {
        SELF(Actor)->header.step += 1;
        dx = g_Game.members[0].pos.x.fixed - 0x428000;
        if (ABS(dx) <= 0x8000 && (Area119_Distance(g_Game.members[0].pos.y.fixed, -0x3E0000) <= 0x10000 || Area119_Distance(g_Game.members[0].pos.y.fixed, -0x3F0000) <= 0x10000)) {
            span                     = -0x100;
            SELF(Actor)->screen_y    = span;
            SELF(Actor)->header.step = 3;
        }
    }
    func_801F3324();
}
