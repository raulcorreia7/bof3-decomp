#include "engine/slus/slus.h"

/* latches the active mode's sub-state flag into g_AreaHeightOffsetEnabled.
 */
MATCH void Area_HeightEnableOffset(void) {
    s32 flag;

    if (SELF(u8) == D_8014626C) {
        flag = g_Game.unk_3E7 & 0x1;
    } else {
        flag = g_Game.current->status.field.flags.unsigned_value & 0x1;
    }
    if (flag != 0) {
        g_AreaHeightOffsetEnabled = 1;
    }
}
