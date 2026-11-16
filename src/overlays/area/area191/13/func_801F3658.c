#include "area191_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F3658(s32 x, s32 y) {
    s32 cell_x;
    s32 cell_y;
    u8  count;

    cell_x = x >> 16;
    cell_y = y >> 16;
    count  = (Area_GetCellCode(cell_x, cell_y) & BYTE_MASK) == 0xA6;
    if ((x & HALF_MASK) != 0) {
        if ((Area_GetCellCode((s16)(cell_x + 1), cell_y) & BYTE_MASK) == 0xA6) {
            count++;
        }
    }
    if ((y & HALF_MASK) != 0) {
        if ((Area_GetCellCode(x >> 16, (s16)((y >> 16) + 1)) & BYTE_MASK) == 0xA6) {
            count++;
        }
    }
    if ((x & HALF_MASK) != 0 && (y & HALF_MASK) != 0) {
        if ((Area_GetCellCode((s16)((x >> 16) + 1), (s16)((y >> 16) + 1)) & BYTE_MASK) == 0xA6) {
            count++;
        }
    }
    if (count != 0) {
        Scene_StartEvent(0x35, 0);
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F3658);
#endif
