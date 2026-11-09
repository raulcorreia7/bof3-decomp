#include "engine/slus/slus.h"

/* copies the `value`-selected area-script record into `dst` through func_8014D54C and re-arms the staged entry. */
MATCH void Actor_SwitchScript(u8 value, u8* dst, s32 size) {
    s32 current;

    Actor_CopyScriptEntry(value, dst, (u16)size);
    if (g_Task->unk_4B == value) {
        current = g_Task->script_pc - 2;
    } else {
        g_Task->unk_4B = value;
        current        = 0;
    }
    Actor_SeekScript(current);
}
