#include "area042_13.h"

MATCH void func_801F3E80(void) {
    SYS_ClearFlag(g_SaveData.scene_event_flags, (FIELD(u8, g_CurrentActor, 0x94u) + 0x10) & BYTE_MASK);
}
