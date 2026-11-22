#include "area104_14.h"

MATCH s32 func_801F66D0(s16 cell_x, s16 cell_y) {
    switch (Area_CellGetCode(cell_x, cell_y) & BYTE_MASK) {
        case 0x00:
        case 0xAF:
        case 0xC0:
            return 0;
        case 0x10:
        case 0x50:
            return 2;
        case 0x40:
            return 1;
        case 0x51: /* the switch tree splits here, so the blocked run needs a case */
            return 3;
        default:
            return 3;
    }
}
