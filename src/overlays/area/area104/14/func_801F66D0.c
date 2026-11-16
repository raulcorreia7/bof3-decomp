#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F66D0(s16 cell_x, s16 cell_y) {
    s32 value;

    value = Area_GetCellCode(cell_x, cell_y) & BYTE_MASK;
    switch (value) {
        case 0x10:
        case 0x50:
            return 2;
        case 0x40:
            return 1;
        case 0x00:
        case 0xAF:
        case 0xC0:
            return 0;
        default:
            return 3;
    }
}
#else
INCLUDE_ASM(func_801F66D0);
#endif
