#include "area140_13.h"

MATCH bool func_801F4058(s16 x, s16 y) {
    if ((Actor_IsAheadBlocked(g_CurrentActor) != 0) && ((Area_CellGetCode(x, y) & BYTE_MASK) != 0x89)) {
        return 1;
    }
    return 0;
}
