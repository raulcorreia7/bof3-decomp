#include "engine/slus/slus.h"

/* stages the selected area-script record. */
MATCH void Actor_StageScriptRecord(s32 value, s32 position, u8* dst, s32 size) {
    Actor_CopyScriptEntry((u8)value, dst, (u16)size);
    g_Task->unk_4B = value;
    Actor_SeekScript(position);
}
