#include "area128_13.h"

MATCH void func_801F31D0(void) {
    u8* record;

    if (D_80143F04 == AREA_ID_STEEL_BEACH_MAP) {
        SYS_SetFlag(g_SceneEventFlags, 0x43);
        SYS_ClearFlag(g_SceneEventFlags, 0x42);
        record = MEM_PTR(u8, MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4);
        while (FIELD(u32, record, 0) != 0) {
            func_801576FC(record);
            record += FIELD(u16, record, 2) * 4 + 4;
        }
    }
    if (g_SceneState.scenario_id >= 11 && SYS_TestFlag(g_SceneEventFlags, 0x43)) {
        Area_SetCellCode(31, 57, 0xC0);
        Area_SetCellCode(32, 57, 0xC0);
        Area_SetCellCode(31, 58, 0xA1);
        Area_SetCellCode(32, 58, 0xA1);
    }
}
