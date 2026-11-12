#include "area140_13.h"

MATCH bool func_801F4058(s16 x, s16 y) {
    if ((func_801A1AE4(g_CurrentActor) != 0) && ((Area_GetCellCode(x, y) & BYTE_MASK) != 0x89)) {
        return 1;
    }
    return 0;
}
