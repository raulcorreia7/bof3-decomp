#include "area049_14.h"

void func_801F2C80(void); /* extern */

MATCH s32 func_801F2CC0(s32 entry_x) {
    if ((entry_x == TO_COORD(77) + COORD_HALF) && (g_GameCellType == 0)) {
        func_801F2C80();
    }
    return 0;
}
