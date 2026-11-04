#include "engine/slus/slus.h"

/* reads the byte at g_AreaCellCodes + g_AreaMapBundle.width_00 * y + x.
 */
MATCH s32 Area_GetCellCode(s32 x, s32 y) {
    return *(u8*)((u8*)g_AreaCellCodes + (s16)y * g_AreaMapBundle.width_00 + (s16)x);
}
