#include "area173_14.h"

MATCH void func_801F4E90(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x58) != 0) {
        g_SaveData.scene_event.mode = 0x26;
        g_SaveData.scene_event.step = 0xA;
    }
}
