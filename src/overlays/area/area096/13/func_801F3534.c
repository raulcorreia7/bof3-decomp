#include "area096_13.h"

MATCH void func_801F3534(void) {
    if ((Area_GetCellCode(65, 57) & BYTE_MASK) == 0) {
        Area_SetCellCode(65, 57, 0x10);
    } else {
        Area_SetCellCode(65, 57, 0);
    }
}
