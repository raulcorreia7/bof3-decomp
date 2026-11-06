#include "area140_13.h"

MATCH void func_801F476C(void) {
    u8* work;

    work = (u8*)g_Task;
    SYS_ClearFlag(g_SaveData.scene_event_flags, work[0xB]);
    work = (u8*)g_Task;
    Area_SetCellPalette(FIELD(s16, work, 0x36), FIELD(s16, work, 0x3A));
    Actor_Clear();
}
