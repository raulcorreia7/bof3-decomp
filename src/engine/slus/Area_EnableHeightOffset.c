#include "engine/slus/slus.h"

/* latches the active mode's sub-state flag into g_AreaHeightOffsetEnabled.
 */
MATCH void Area_EnableHeightOffset(void) {
    s32 flag;

    if ((u8*)g_Task == D_8014626C) {
        flag = D_80146277 & 0x1;
    } else {
        flag = g_Game.current->status.field.flags_12C.u8_value & 0x1;
    }
    if (flag != 0) {
        g_AreaHeightOffsetEnabled = 1;
    }
}
