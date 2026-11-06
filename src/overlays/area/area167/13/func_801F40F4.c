#include "area167_13.h"

MATCH void func_801F40F4(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x4B) == 0) {
        g_ScriptState->cursor += 3;
    }
}
