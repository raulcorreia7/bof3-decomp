#include "engine/slus/slus.h"

/* latches the active mode's sub-state flag into D_80149340.
 */
MATCH void Area_EnableHeightOffset(void) {
    s32 flag;

    if ((u8*)g_SpadWork == D_8014626C) {
        flag = D_80146277 & 1;
    } else {
        flag = g_GameState->unk_12C[0] & 1;
    }
    if (flag != 0) {
        D_80149340 = 1;
    }
}
