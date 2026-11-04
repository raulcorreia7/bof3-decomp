#include "area095_13.h"

MATCH void func_801F35A4(void) {
    if ((Area_GetCellCode(0x41, 0x39) & BYTE_MASK) == 0) {
        Area_SetCellCode(0x41, 0x39, 0x10);
    } else {
        Area_SetCellCode(0x41, 0x39, 0);
    }
}
