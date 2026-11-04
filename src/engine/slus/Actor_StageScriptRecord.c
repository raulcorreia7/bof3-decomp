#include "engine/slus/slus.h"

/* stages the selected area-script record: func_8014D54C copies it to
 * dst, the scratchpad work byte at 0x4B takes the staged index, then
 * func_8014D910 re-arms the staged position from the staged index.
 */
MATCH void Actor_StageScriptRecord(s32 value, s32 position, u8* dst, s32 size) {
    Actor_CopyScriptEntry((u8)value, dst, (u16)size);
    g_SpadWork->unk_4B = value;
    Actor_SeekScript((u16)position);
}
