#include "area119_13.h"

MATCH void func_801F3298(void) {
    if (SYS_TestFlag(g_SceneFlagRows[9], 15) != 0) {
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x3E + 0x41] = 0xA1;
        g_AreaCellCodes[((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 0x3F + 0x41] = 0xA1;
        SELF(Actor)->header.step                                                = 1;
    }
    func_801F3324();
}
