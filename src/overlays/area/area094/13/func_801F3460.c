#include "area094_13.h"

MATCH void func_801F3460(void) {
    u8* record;

    if (D_80143F04 == 0x79) {
        SYS_SetFlag(g_SceneEventFlags, 0x42);
        SYS_ClearFlag(g_SceneEventFlags, 0x43);
        record = MEM_PTR(u8, MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4);
        while (FIELD(u32, record, 0) != 0) {
            func_801576FC(record);
            record += FIELD(u16, record, 2) * 4 + 4;
        }
    }
}
