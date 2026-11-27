#include "area011_13.h"

MATCH void func_801F2CC4(void) {
    u32* p;

    if (SYS_TestFlag(g_SceneFlagRows[SCENARIO_DESERT_OF_DEATH], 19) == 0) {
        return;
    }
    if (SYS_TestFlag(g_SceneFlagRows[SCENARIO_DESERT_OF_DEATH], 20) != 0) {
        return;
    }
    p = (u32*)(MAP_BUNDLE_BASE + (AREA_MAP_BUNDLE->record_list_offset << 2));
    if (*p == 0) {
        return;
    }
    while (*p != 0) {
        u32 v = *p;
        if ((v & AREA_RECORD_TYPE_MASK) == AREA_RECORD_TYPE_81) {
            p += 2;
            p[1] = 0x21080000;
            p[0] = 0x21080000;
            return;
        }
        p = (u32*)((u8*)p + ((v >> 14) & 0x3FC));
    }
}
