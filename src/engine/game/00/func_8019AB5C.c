#include "game_00.h"

MATCH void func_8019AB5C(void) {
    Actor* work;
    u8     value;

    work  = g_Task;
    value = work->unk_09;
    if (value == 0) {
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x1Cu);
        Actor_Clear();
        return;
    }
    work->unk_09 = (value - 1);
}
