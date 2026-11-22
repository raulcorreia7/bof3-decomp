#include "engine/slus/slus.h"

/* latches the active mode's sub-state flag into g_AreaHeightOffsetEnabled.
 */
MATCH void Area_HeightEnableOffset(void) {
    s32 flag;

    if (TASK(u8) == D_8014626C) {
        flag = D_80146277 & 0x1;
    } else {
        flag = g_Game.current->status.field.flags.unsigned_value & 0x1;
    }
    if (flag != 0) {
        g_AreaHeightOffsetEnabled = 1;
    }
}
