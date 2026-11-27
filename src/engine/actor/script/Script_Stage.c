#include "engine/slus/slus.h"

/* stages the selected area-script record: func_8014D54C copies it to
 * staging, the scratchpad work byte at 0x4B takes the staged index, then
 * func_8014D910 re-arms the staged position from the staged index.
 */
MATCH void Script_Stage(s32 script_index, s32 position, u8* staging, s32 size) {
    Script_CopyRecord((u8)script_index, staging, (u16)size);
    SELF(Actor)->script_record = script_index;
    Script_Seek(position);
}
