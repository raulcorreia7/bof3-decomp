#include "area051_13.h"

MATCH void func_801F2D00(void) {
    u32* p;

    if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 19) == 0) {
        return;
    }
    if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 20) != 0) {
        return;
    }
    p = (u32*)(MAP_BUNDLE_BASE + (((AreaMapBundle*)MAP_BUNDLE_BASE)->record_list_offset << 2));
    if (*p == 0) {
        return;
    }
    while (*p != 0) {
        u32 v = *p;
        if ((v & AREA_RECORD_TYPE_MASK) == AREA_RECORD_TYPE_81) {
            p += 2;
            p[1] = AREA051_RECORD_81_WORD;
            p[0] = AREA051_RECORD_81_WORD;
            return;
        }
        p = (u32*)((u8*)p + ((v >> 14) & 0x3FC));
    }
}
