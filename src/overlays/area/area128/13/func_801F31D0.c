#include "area128_13.h"
#include "slus/data.h"

void func_801576FC(u8* record);
void func_801A4BC0(s32 x, s32 y, s32 value);

MATCH void func_801F31D0(void) {
    u8* record;

    if (D_80143F04 == 0x79) {
        SYS_SetFlag(g_SceneEventFlags, 0x43);
        SYS_ClearFlag(g_SceneEventFlags, 0x42);
        record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4;
        while (*(u32*)record != 0) {
            func_801576FC(record);
            record += *(u16*)(record + 2) * 4 + 4;
        }
    }
    if (g_SceneState.scenario_id >= 0xB) {
        if (SYS_TestFlag(g_SceneEventFlags, 0x43)) {
            func_801A4BC0(0x1F, 0x39, 0xC0);
            func_801A4BC0(0x20, 0x39, 0xC0);
            func_801A4BC0(0x1F, 0x3A, 0xA1);
            func_801A4BC0(0x20, 0x3A, 0xA1);
        }
    }
}
