#include "area117_13.h"

MATCH void func_801F2C60(void) {
    g_Task->screen_y = 0;
    if (!SYS_TestFlag(D_80144ED0, 0xC)) {
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x15 + 1] = 0x50;
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x16 + 1] = 0x50;
        g_Task->header.step                                                  = 5;
    } else {
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x15 + 1] = 0xA1;
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x16 + 1] = 0xA1;
        g_Task->header.step += 1;
        if (abs(g_Game.members[0].pos.x.fixed - TO_COORD_HALF(2)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x15)) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - TO_COORD(0x16)) <= TO_COORD(1)) {
                /* FAKE: retail writes the row through a signed view (li -0x100). */
                *(s16*)&g_Task->screen_y = -0x100;
                g_Task->header.step      = 3;
            }
        }
    }
    func_801F314C();
}
